package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
)

// Struct for YouTube API Response
type YouTubeResponse struct {
	Items []struct {
		Snippet struct {
			Title       string `json:"title"`
			Description string `json:"description"`
		} `json:"snippet"`
	} `json:"items"`
}

func getYouTubeData(videoID string, apiKey string) {
	url := fmt.Sprintf("https://www.googleapis.com/youtube/v3/videos?part=snippet&id=%s&key=%s", videoID, apiKey)
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println("Error fetching data:", err)
		return
	}
	defer resp.Body.Close()

	body, _ := ioutil.ReadAll(resp.Body)
	var data YouTubeResponse
	json.Unmarshal(body, &data)

	for _, item := range data.Items {
		fmt.Println("Title:", item.Snippet.Title)
		fmt.Println("Description:", item.Snippet.Description)
	}
}

func main() {
	// Call YouTube API with video ID and API key
	videoID := "dQw4w9WgXcQ" // Example YouTube video ID
	apiKey := "YOUR_YOUTUBE_API_KEY" // Replace with your API Key
	getYouTubeData(videoID, apiKey)
}
