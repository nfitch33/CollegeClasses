# summarize.py (Ollama Python client version)
from ollama import chat

def summarize_text(chunks, query):
    """
    Summarize chunks individually, then combine into a final summary.
    """

    partial_summaries = []

    # Step 1: Summarize each chunk
    for i, chunk in enumerate(chunks):
        print(f"Summarizing chunk {i+1}/{len(chunks)}...")

        response = chat(
            model="llama3",   # change to "mistral" or "gemma:2b" if needed
            messages=[
                {
                    "role": "user",
                    "content": f"""
Summarize this textbook section in relation to '{query}'.

Text:
{chunk}

Return concise bullet points.
"""
                }
            ]
        )

        summary = response["message"]["content"]
        partial_summaries.append(summary)

    # Step 2: Combine summaries
    combined = "\n\n".join(partial_summaries)

    final_response = chat(
        model="llama3",
        messages=[
            {
                "role": "user",
                "content": f"""
Combine the following summaries into a clear, high-level summary about '{query}'.

{combined}

Return only key points.
"""
            }
        ]
    )

    final_summary = final_response["message"]["content"]
    return final_summary