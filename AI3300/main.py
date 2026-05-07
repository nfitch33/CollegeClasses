# main.py
import argparse
import os
from utils import extract_text_from_pdf, chunk_text
from retrieve import embed_chunks, retrieve_top_k
from summarize import summarize_text

def main():
    parser = argparse.ArgumentParser(description="Textbook Agent")
    parser.add_argument("--pdf", required=True, help="Path to textbook PDF")
    parser.add_argument("--prompt", required=True, help="Query / keypoints")
    parser.add_argument("--top_k", type=int, default=5, help="Number of chunks to retrieve")
    args = parser.parse_args()

    print("Extracting text from PDF...")
    text = extract_text_from_pdf(args.pdf)

    print("Splitting text into chunks...")
    chunks = chunk_text(text)

    print("Embedding chunks...")
    embeddings = embed_chunks(chunks)

    print(f"Retrieving top {args.top_k} relevant chunks...")
    top_chunks = retrieve_top_k(chunks, embeddings, args.prompt, k=args.top_k)

    print("Summarizing retrieved content...")
    summary = summarize_text(top_chunks, args.prompt)

    print("\n===== High-Level Summary =====\n")
    print(summary)

    # Save summary to a text file
    os.makedirs("summaries", exist_ok=True)
    output_file = f"summaries/{os.path.basename(args.pdf).replace('.pdf','_summary.txt')}"
    with open(output_file, "w", encoding="utf-8") as f:
        f.write(summary)

    print(f"\nSummary saved to: {output_file}")

if __name__ == "__main__":
    main()