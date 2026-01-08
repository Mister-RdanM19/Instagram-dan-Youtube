import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import org.json.JSONObject;

public class Main {
    public static void getYouTubeData(String videoID, String apiKey) throws Exception {
        String url = "https://www.googleapis.com/youtube/v3/videos?part=snippet&id=" + videoID + "&key=" + apiKey;
        HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();
        connection.setRequestMethod("GET");

        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String inputLine;
        StringBuilder response = new StringBuilder();
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();

        // Parse JSON Response
        JSONObject myResponse = new JSONObject(response.toString());
        String title = myResponse.getJSONArray("items").getJSONObject(0).getJSONObject("snippet").getString("title");
        String description = myResponse.getJSONArray("items").getJSONObject(0).getJSONObject("snippet").getString("description");

        System.out.println("Title: " + title);
        System.out.println("Description: " + description);
    }

    public static void main(String[] args) {
        try {
            String videoID = "dQw4w9WgXcQ"; // Example YouTube video ID
            String apiKey = "YOUR_YOUTUBE_API_KEY"; // Replace with your API Key
            getYouTubeData(videoID, apiKey);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
