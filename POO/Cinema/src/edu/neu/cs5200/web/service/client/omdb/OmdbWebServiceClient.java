package edu.neu.cs5200.web.service.client.omdb;

import Buttons.MainFrame;
import java.io.*;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
public class OmdbWebServiceClient {

    public static final String SEARCH_URL = "https://www.omdbapi.com/?s=TITLE&apikey=APIKEY";
    public static final String SEARCH_BY_IMDB_URL = "https://www.omdbapi.com/?i=IMDB&apikey=APIKEY";

    public static String sendGetRequest(String requestUrl){
        StringBuffer response = new StringBuffer();
        try{
            URL url = new URL(requestUrl);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setRequestProperty("Accept","*/*");
            connection.setRequestProperty("Content-Type","application/json; charset=UTF-8");
            InputStream stream = connection.getInputStream();
            InputStreamReader reader = new InputStreamReader(stream);
            BufferedReader buffer = new BufferedReader(reader);
            String line;
            while((line = buffer.readLine())!=null){
                response.append(line);
            }
        } catch (MalformedURLException e){
            e.printStackTrace();
        }
        catch (IOException e){
            e.printStackTrace();
        }

        return response.toString();
    }

    public static String searchMovieByTitle(String title, String key){
        try{
            title = URLEncoder.encode(title, "UTF-8");
        } catch(UnsupportedEncodingException e){
            e.printStackTrace();
        }

        String requestURL = SEARCH_URL.replaceAll("TITLE",title).replaceAll("APIKEY",key);
        return sendGetRequest(requestURL);
    }
    public static String searchMovieByImdb(String imdb, String key){
        String requestURL = SEARCH_BY_IMDB_URL.replaceAll("IMDB", imdb).replaceAll("APIKEY",key);
        return sendGetRequest(requestURL);
    }
    public static void main(String[] args){
        MainFrame myFrame = new MainFrame();
        myFrame.setVisible(true);
    }
}
