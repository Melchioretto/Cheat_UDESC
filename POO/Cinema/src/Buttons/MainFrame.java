package Buttons;

import edu.neu.cs5200.web.service.client.omdb.OmdbWebServiceClient;
import org.json.JSONArray;
import org.json.JSONObject;

import javax.swing.*;
import java.util.ArrayList;

public class MainFrame extends JFrame{
    private JTextField tfCodigoOMDB;
    private JTextField tfNomeFilme;
    private JButton OKButton;
    private JPanel mainPanel;
    private JLabel lbFilme;
    private ArrayList<JButton> infoFilmeButton = new ArrayList<>();

    public  MainFrame(){
        setContentPane(mainPanel);
        setTitle("Cinema");
        setSize(1000,800);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        OKButton.addActionListener(e -> {

            String codigoOMDB = tfCodigoOMDB.getText();
            String nomefilme = tfNomeFilme.getText();
            for(JButton buttonIteration : infoFilmeButton){
                mainPanel.remove(buttonIteration);
            }
            infoFilmeButton.clear();
            String jsonResponse = OmdbWebServiceClient.searchMovieByTitle(nomefilme, codigoOMDB);
            String json_str = jsonResponse;

            JSONObject obj = new JSONObject(json_str);

                JSONArray filmes = obj.getJSONArray("Search");
                String texto="<html>";

                for (int i = 0;i<filmes.length();i++){
                    obj = new JSONObject(filmes.get(i).toString());
                    System.out.println(obj.getString("Title"));
                    texto+= obj.getString("Title")+"<br>";
                    JButton buttoninfo= new JButton(obj.getString("Title"));
                    infoFilmeButton.add(buttoninfo);
                    mainPanel.setLayout(null);
                    buttoninfo.setBounds(20,100+i*40,600,30);
                    buttoninfo.setActionCommand(obj.getString("imdbID"));
                    mainPanel.add(buttoninfo);
                }
                lbFilme.setText(texto+"</html>");
                for(JButton buttonIteration : infoFilmeButton){
                    buttonIteration.addActionListener(e1 ->{
                        String imdbId = e1.getActionCommand();
                        Information myinfo = new Information(imdbId, codigoOMDB);
                        myinfo.setVisible(true);
                    });
                }

        });
    }
}
//String jsonResponse = OmdbWebServiceClient.searchMovieByImdb("tt0372784","47925545");

//String jsonResponse = OmdbWebServiceClient.searchMovieByImdb("tt0372784","47925545");
//System.out.println(jsonResponse);