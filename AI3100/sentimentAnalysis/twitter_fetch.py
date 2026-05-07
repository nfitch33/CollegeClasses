import requests

def fetch_latest_tweets(username, bearer_token, max_results=10):
    """
    Fetches the most recent tweets from a Twitter/X account using API v2.
    Returns a list of tweet texts.
    """

    headers = {
        "Authorization": f"Bearer {bearer_token}"
    }

    # Step 1: Get user ID from username
    url_user = f"https://api.twitter.com/2/users/by/username/{username}"
    user_response = requests.get(url_user, headers=headers).json()

    if "data" not in user_response:
        raise Exception(f"Could not retrieve user '{username}'. "
                        "Check username or Bearer Token.")

    user_id = user_response["data"]["id"]

    # Step 2: Fetch most recent tweets
    url_tweets = (
        f"https://api.twitter.com/2/users/{user_id}/tweets"
        f"?exclude=replies,retweets&max_results={max_results}"
    )

    tweets_response = requests.get(url_tweets, headers=headers).json()

    if "data" not in tweets_response:
        return []

    return [t["text"] for t in tweets_response["data"]]
