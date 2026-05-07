import numpy as np
from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity

# Load model (CUDA or CPU)
model = SentenceTransformer("all-MiniLM-L6-v2")

def embed_chunks(chunks, batch_size=64):
    """
    Convert chunk text into embeddings using batch encoding.
    """
    texts = [c["text"] for c in chunks]
    embeddings = model.encode(
        texts,
        convert_to_numpy=True,
        batch_size=batch_size,
        show_progress_bar=True
    )
    return embeddings

def retrieve_top_k(chunks, chunk_embeddings, query, k=5):
    """
    Retrieve top-k most relevant chunks with metadata.
    """
    query_emb = model.encode([query], convert_to_numpy=True)
    similarities = cosine_similarity(query_emb, chunk_embeddings)[0]
    top_indices = similarities.argsort()[::-1][:k]
    results = []
    for i in top_indices:
        results.append({
            "text": chunks[i]["text"],
            "page": chunks[i]["page"],
            "file": chunks[i]["file"],
            "score": float(similarities[i])
        })
    return results