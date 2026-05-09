import requests

def get_weather():
	res = requests.get("https://wttr.in/")
	return res.text
