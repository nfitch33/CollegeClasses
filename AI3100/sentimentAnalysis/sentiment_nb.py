#!/usr/bin/env python3
"""
Sentiment Analysis System (Manual Input with --- Separators)

- Trains Naive Bayes on Yelp Polarity (first run only)
- Saves/loads model automatically
- Supports incremental learning
- Reads posts from a .txt file (separated by ---)
- Classifies each post as positive/negative
"""

import os
import joblib
import numpy as np
from datasets import load_dataset
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import CountVectorizer

# ============================================
# CONFIG
# ============================================
MODEL_PATH = "nb_model.pkl"
VECTORIZER_PATH = "vectorizer.pkl"
INPUT_FILE = "posts.txt"      # File containing messages
SEPARATOR = "---"             # Text used to separate posts


# ============================================
# MODEL LOADING / SAVING
# ============================================

def load_or_initialize_model():
    """Load model if exists, otherwise create a fresh one."""
    if os.path.exists(MODEL_PATH) and os.path.exists(VECTORIZER_PATH):
        print("Loading existing model...")
        clf = joblib.load(MODEL_PATH)
        vectorizer = joblib.load(VECTORIZER_PATH)
        return clf, vectorizer, True

    print("No saved model found — initializing new model.")
    clf = MultinomialNB()
    vectorizer = CountVectorizer(stop_words='english', min_df=5)
    return clf, vectorizer, False


def save_model(clf, vectorizer):
    """Save classifier and vectorizer."""
    joblib.dump(clf, MODEL_PATH)
    joblib.dump(vectorizer, VECTORIZER_PATH)
    print("Model saved.")


# ============================================
# TRAINING
# ============================================

def initial_train():
    """Perform initial training on Yelp Polarity dataset."""
    clf, vectorizer, loaded = load_or_initialize_model()

    if loaded:
        print("Model already exists. Skipping initial training.")
        return clf, vectorizer

    print("Downloading Yelp Polarity training dataset...")
    ds_train = load_dataset("yelp_polarity", split="train")

    texts = ds_train["text"]
    labels = np.array(ds_train["label"])

    print("Vectorizing text...")
    X_train = vectorizer.fit_transform(texts)

    print("Training Naive Bayes...")
    clf.partial_fit(X_train, labels, classes=np.array([0, 1]))

    save_model(clf, vectorizer)
    print("Initial training complete.")
    return clf, vectorizer


def incremental_train(new_texts, new_labels):
    """Add new labeled examples to improve the model."""
    clf, vectorizer, loaded = load_or_initialize_model()
    if not loaded:
        raise RuntimeError("Model not trained yet. Run initial_train first.")

    X_new = vectorizer.transform(new_texts)
    clf.partial_fit(X_new, np.array(new_labels))
    save_model(clf, vectorizer)

    print("Incremental training complete.")


# ============================================
# POST FILE READER (--- separator)
# ============================================

def read_posts_from_file(path, sep="---"):
    """Read multi-line posts separated by a custom separator."""
    if not os.path.exists(path):
        print(f"ERROR: Cannot find file '{path}'")
        return []

    with open(path, "r", encoding="utf-8") as f:
        content = f.read()

    # Split using separator token
    raw_posts = content.split(sep)

    # Clean and return non-empty blocks
    posts = [p.strip() for p in raw_posts if p.strip()]
    return posts


# ============================================
# CLASSIFICATION
# ============================================

def classify_posts(posts):
    clf, vectorizer, loaded = load_or_initialize_model()

    if not loaded:
        raise RuntimeError("Model not trained yet.")

    X = vectorizer.transform(posts)
    preds = clf.predict(X)
    probs = clf.predict_proba(X)

    results = []
    for text, pred, proba in zip(posts, preds, probs):
        sentiment = "positive" if pred == 1 else "negative"
        results.append((text, sentiment, proba))

    return results


# ============================================
# MAIN PROGRAM
# ============================================

def main():
    print("\n=== Step 1: Train or Load Model ===")
    clf, vectorizer = initial_train()

    print("\n=== Step 2: Reading posts from file ===")
    posts = read_posts_from_file(INPUT_FILE, SEPARATOR)

    if not posts:
        print("No posts found. Add content to posts.txt separated by ---")
        return

    print(f"\nLoaded {len(posts)} posts:")
    for i, post in enumerate(posts, 1):
        print(f"\n--- POST {i} ---\n{post}")

    print("\n=== Step 3: Running Sentiment Analysis ===")
    results = classify_posts(posts)

    for i, (text, label, prob) in enumerate(results, 1):
        print("\n--------------------------------")
        print(f"POST {i}:")
        print("Text:", text)
        print("Sentiment:", label)
        prob_str = [f"{p:.4f}" for p in prob]
        print("Probabilities:", prob_str)



if __name__ == "__main__":
    main()
