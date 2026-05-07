import numpy as np
from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity

# Load a sentence embedding model
model = SentenceTransformer('all-MiniLM-L6-v2')

def embed_chunks(chunks):
    """Convert text chunks into embeddings."""
    embeddings = model.encode(chunks, convert_to_numpy=True)
    return embeddings

def retrieve_top_k(chunks, chunk_embeddings, query, k=5):
    """Retrieve top-k most relevant chunks for a query."""
    query_emb = model.encode([query], convert_to_numpy=True)
    similarities = cosine_similarity(query_emb, chunk_embeddings)[0]
    top_indices = similarities.argsort()[::-1][:k]
    top_chunks = [chunks[i] for i in top_indices]
    return top_chunks