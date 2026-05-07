import pdfplumber

def extract_text_from_pdf(pdf_path):
    """Extract all text from a PDF file."""
    text = ""
    with pdfplumber.open(pdf_path) as pdf:
        for page in pdf.pages:
            text += page.extract_text() + "\n"
    return text

def chunk_text(text, chunk_size=500):
    """
    Split text into chunks of approximately chunk_size words.
    """
    words = text.split()
    chunks = []
    for i in range(0, len(words), chunk_size):
        chunk = " ".join(words[i:i+chunk_size])
        chunks.append(chunk)
    return chunks