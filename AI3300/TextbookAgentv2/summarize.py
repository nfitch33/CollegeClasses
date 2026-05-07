from ollama import chat

def summarize_text(chunks, query):
    """
    Summarize across multiple documents with file + page references.
    """
    partial_summaries = []

    for i, chunk in enumerate(chunks):
        print(f"   • Chunk {i+1}/{len(chunks)} ({chunk['file']} - Page {chunk['page']})")
        response = chat(
            model="llama3",
            messages=[{
                "role": "user",
                "content": f"""
You are helping a student study across multiple textbooks.

Summarize the content relevant to: "{query}"

Source:
File: {chunk['file']}
Page: {chunk['page']}
Relevance Score: {chunk['score']:.4f}

Text:
{chunk['text']}

Return concise bullet points and include:
(File Name, Page X)
"""
            }]
        )
        partial_summaries.append(response["message"]["content"])

    combined = "\n\n".join(partial_summaries)
    final_response = chat(
        model="llama3",
        messages=[{
            "role": "user",
            "content": f"""
Combine the following into a clean, high-level answer for: "{query}"

Requirements:
- Group similar ideas
- Remove redundancy
- Keep citations in format (File, Page X)
- Clearly show which document each idea came from

{combined}
"""
        }]
    )

    return final_response["message"]["content"]