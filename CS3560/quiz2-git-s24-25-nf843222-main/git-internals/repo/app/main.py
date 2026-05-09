import requests

from service import get_weather

if __name__ == "__main__":
    print("Hi!, weather today is")
    res = get_weather()
    print(res)
