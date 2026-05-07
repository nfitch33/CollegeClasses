import os
import pdfplumber

def load_pdfs_from_directory(directory):
    """
    Load all PDFs in a directory.
    Returns: list of {file, page, text}
    """
    all_pages = []
    for filename in os.listdir(directory):
        if filename.lower().endswith(".pdf"):
            pdf_path = os.path.join(directory, filename)
            print(f"   • Loading {filename}")
            with pdfplumber.open(pdf_path) as pdf:
                for i, page in enumerate(pdf.pages):
                    text = page.extract_text()
                    if text and text.strip():
                        all_pages.append({
                            "file": filename,
                            "page": i + 1,
                            "text": text
                        })
    return all_pages

def chunk_text(pages, chunk_size=500):
    """
    Split pages into chunks while preserving file + page metadata.
    Returns: list of {text, page, file}
    """
    chunks = []
    for page in pages:
        words = page["text"].split()
        for i in range(0, len(words), chunk_size):
            chunk_words = words[i:i + chunk_size]
            chunk_str = " ".join(chunk_words)
            chunks.append({
                "text": chunk_str,
                "page": page["page"],
                "file": page["file"]
            })
    return chunks