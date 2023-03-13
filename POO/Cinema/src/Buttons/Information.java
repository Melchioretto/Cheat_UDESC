package Buttons;

import edu.neu.cs5200.web.service.client.omdb.OmdbWebServiceClient;
import org.json.JSONObject;

import javax.swing.*;
import java.net.MalformedURLException;
import java.net.URL;

public class Information extends JFrame {
    private JPanel infoPanel;
    private JLabel lbInfo;

    public  Information(String imdbId, String codigoOMDB){
        setContentPane(infoPanel);
        setTitle("Informações");
        setSize(1600,800);
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        String json_info = OmdbWebServiceClient.searchMovieByImdb(imdbId, codigoOMDB);
        JSONObject obj = new JSONObject(json_info);
        String textoInfo="<html>";
        textoInfo+= obj.getString("Title")+"<br>"+obj.getString("Year")+"<br>"+ obj.getString("Rated")+"<br>"+ obj.getString("Released")+"<br>"+ obj.getString("Runtime")
                +"<br>"+ obj.getString("Genre")+"<br>"+ obj.getString("Director")+"<br>"+ obj.getString("Writer")+"<br>"+ obj.getString("Actors")+"<br>"+ obj.getString("Plot")
                +"<br>"+ obj.getString("Language")+"<br>"+ obj.getString("Country")+"<br>"+ obj.getString("Awards")+"<br>"+ obj.getString("imdbID")
                +"<br>"+ obj.getString("Type");
        try {
            URL imagem = new URL(obj.getString("Poster"));
            lbInfo.setIcon(new ImageIcon(imagem));
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        lbInfo.setText(textoInfo+"</html>");
    }

}