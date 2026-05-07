import argparse
import os
from utils import load_pdfs_from_directory, chunk_text
from retrieve import embed_chunks, retrieve_top_k
from summarize import summarize_text
import pickle
import numpy as np

EMBEDDINGS_CACHE = "cache/embeddings.npy"
CHUNKS_CACHE = "cache/chunks.pkl"

def run_query(chunks, embeddings, query, top_k):
    print(f"\n🔍 Searching for: {query}")
    top_chunks = retrieve_top_k(chunks, embeddings, query, k=top_k)
    print("🧠 Summarizing results...")
    summary = summarize_text(top_chunks, query)
    print("\n===== Answer =====\n")
    print(summary)
    return summary

def main():
    parser = argparse.ArgumentParser(description="Multi-PDF Textbook Agent with Batched Embeddings")
    parser.add_argument("--dir", required=True, help="Directory containing PDFs")
    parser.add_argument("--prompt", help="Query / keypoints")
    parser.add_argument("--top_k", type=int, default=5)
    parser.add_argument("--interactive", action="store_true")
    parser.add_argument("--batch_size", type=int, default=64)
    args = parser.parse_args()

    os.makedirs("cache", exist_ok=True)
    os.makedirs("summaries", exist_ok=True)

    print("📂 Loading PDFs from directory...")
    pages = load_pdfs_from_directory(args.dir)

    print("✂️ Chunking text...")
    chunks = chunk_text(pages)

    # --- Try to load cached embeddings ---
    if os.path.exists(EMBEDDINGS_CACHE) and os.path.exists(CHUNKS_CACHE):
        print("💾 Loading cached embeddings...")
        embeddings = np.load(EMBEDDINGS_CACHE)
        with open(CHUNKS_CACHE, "rb") as f:
            cached_chunks = pickle.load(f)
        if len(cached_chunks) == len(chunks):
            chunks = cached_chunks
        else:
            print("⚠️ Chunk count mismatch, recomputing embeddings")
            embeddings = embed_chunks(chunks, batch_size=args.batch_size)
            np.save(EMBEDDINGS_CACHE, embeddings)
            with open(CHUNKS_CACHE, "wb") as f:
                pickle.dump(chunks, f)
    else:
        print("🔢 Computing embeddings (batched)...")
        embeddings = embed_chunks(chunks, batch_size=args.batch_size)
        np.save(EMBEDDINGS_CACHE, embeddings)
        with open(CHUNKS_CACHE, "wb") as f:
            pickle.dump(chunks, f)

    # --- Single query mode ---
    if args.prompt and not args.interactive:
        summary = run_query(chunks, embeddings, args.prompt, args.top_k)
        output_file = f"summaries/multi_pdf_summary.txt"
        with open(output_file, "w", encoding="utf-8") as f:
            f.write(summary)
        print(f"\n💾 Saved to: {output_file}")
    # --- Interactive mode ---
    else:
        print("\n💬 Ask questions across all PDFs (type 'exit' to quit)\n")
        while True:
            query = input("> ")
            if query.lower() in ["exit", "quit"]:
                break
            run_query(chunks, embeddings, query, args.top_k)

if __name__ == "__main__":
    main()