package Lab11;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileFilter;
import java.io.IOException;

public class Paint extends JFrame {
    private final int FRAME_WIDTH = 720;
    private final int FRAME_HEIGHT = 560;
    private final int BUTTON_WIDTH = 175;
    private final int BUTTON_HEIGHT = 40;
    private final int IMAGE_WIDTH = 1024;
    private final int IMAGE_HEIGHT = 768;

    private int x1, x2, y1, y2;

    private JButton btnSave;
    private JButton btnOpen;
    private JButton btnRed;
    private JButton btnGreen;
    private JButton btnBlue;
    private JButton btnYellow;

    private Color penColor;
    private JSlider slider;
    private JFileChooser fileChooser;

    private File file;
    private FileNameExtensionFilter imageFileFilter;

    private JScrollPane scrollPane;
    private Graphics2D displayedImageGraphics;
    private Graphics2D bufferedImageGraphics;

    private DrawArea drawArea;

    public Paint() {
        super("Paint");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(400, 200, FRAME_WIDTH, FRAME_HEIGHT);
        setResizable(false);

        penColor = Color.BLACK;
        slider = new JSlider(1,20,10);
        fileChooser = new JFileChooser();
        imageFileFilter = new FileNameExtensionFilter("Image files",
                "jpg", "jpeg", "png", "JPG", "JPEG", "PNG");

        btnSave = new JButton("Save File");
        btnOpen = new JButton("Open File");
        btnRed =  new JButton();
        btnGreen =  new JButton();
        btnBlue =  new JButton();
        btnYellow =  new JButton();
       
        drawArea = new DrawArea();
        
        btnGreen.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                penColor = Color.GREEN;
            }
        });
        
        btnRed.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                penColor = Color.RED;
            }
        });
        
        btnBlue.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                penColor = Color.BLUE;
            }
        });
        
        btnYellow.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                penColor = Color.YELLOW;
            }
        });

        btnSave.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
            	fileChooser.setFileFilter(imageFileFilter);
                File workingDirectory = new File(System.getProperty("user.dir"));
                fileChooser.setCurrentDirectory(workingDirectory);
                int choosedOption = fileChooser.showOpenDialog(null);

                if (choosedOption == JFileChooser.APPROVE_OPTION) {
                    file = fileChooser.getSelectedFile();

                    try {
                        ImageIO.write(drawArea.getBufferedImage(), "png", file);
                    } catch (IOException exception) {
                        JOptionPane.showMessageDialog(null, "Incorrect output file");
                    }
                }
            }
        });

        btnOpen.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser.setFileFilter(imageFileFilter);
                File workingDirectory = new File(System.getProperty("user.dir"));
                fileChooser.setCurrentDirectory(workingDirectory);
                int choosedOption = fileChooser.showOpenDialog(null);

                if (choosedOption == JFileChooser.APPROVE_OPTION) {
                    file = fileChooser.getSelectedFile();

                    try {
                        drawArea.setBufferedImage(ImageIO.read(file));
                    } catch (IOException exception) {
                        JOptionPane.showMessageDialog(null, "Incorrect input file");
                    }
                }
            }
        });

        scrollPane = new JScrollPane(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
        drawArea.setPreferredSize(new Dimension(IMAGE_WIDTH, IMAGE_HEIGHT));
        scrollPane.getViewport().add(drawArea, null);

        JPanel buttonsPanel = new JPanel();
        buttonsPanel.setLayout(new FlowLayout());

        buttonsPanel.add(btnSave);
        buttonsPanel.add(btnOpen);
        buttonsPanel.add(slider);

        btnSave.setPreferredSize(new Dimension(BUTTON_WIDTH, BUTTON_HEIGHT));
        btnOpen.setPreferredSize(new Dimension(BUTTON_WIDTH, BUTTON_HEIGHT));
        
        JPanel colorButtonPanel = new JPanel();
        colorButtonPanel.setLayout(new GridLayout(4, 1, 15, 15));
        
        colorButtonPanel.add(btnBlue);
        colorButtonPanel.add(btnGreen);
        colorButtonPanel.add(btnRed);
        colorButtonPanel.add(btnYellow);
        
        btnBlue.setPreferredSize(new Dimension(BUTTON_HEIGHT, BUTTON_HEIGHT));
        btnBlue.setBackground(Color.BLUE);
        btnGreen.setPreferredSize(new Dimension(BUTTON_HEIGHT, BUTTON_HEIGHT));
        btnGreen.setBackground(Color.GREEN);
        btnRed.setPreferredSize(new Dimension(BUTTON_HEIGHT, BUTTON_HEIGHT));
        btnRed.setBackground(Color.RED);
        btnYellow.setPreferredSize(new Dimension(BUTTON_HEIGHT, BUTTON_HEIGHT));
        btnYellow.setBackground(Color.YELLOW);
        

        MouseAdapter displayedImageMsAd = new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                super.mousePressed(e);
                x1 = e.getX();
                y1 = e.getY();
            }

            @Override
            public void mouseDragged(MouseEvent e) {
                super.mouseDragged(e);
                displayedImageGraphics = (Graphics2D) drawArea.getGraphics();
                bufferedImageGraphics = (Graphics2D) drawArea.getBufferedImage().getGraphics();
                x2 = e.getX();
                y2 = e.getY();

                displayedImageGraphics.setColor(penColor);
                displayedImageGraphics.setStroke(new BasicStroke(slider.getValue()));
                displayedImageGraphics.drawLine(x1, y1, x2, y2);
                bufferedImageGraphics.setColor(penColor);
                bufferedImageGraphics.setStroke(new BasicStroke(slider.getValue()));
                bufferedImageGraphics.drawLine(x1, y1, x2, y2);

                x1 = x2;
                y1 = y2;
            }
        };

        drawArea.addMouseListener(displayedImageMsAd);
        drawArea.addMouseMotionListener(displayedImageMsAd);

        JPanel finalPanel = new JPanel();
        finalPanel.setLayout(new BorderLayout());

        finalPanel.add(buttonsPanel, BorderLayout.NORTH);
        finalPanel.add(colorButtonPanel, BorderLayout.WEST);
        finalPanel.add(scrollPane, BorderLayout.CENTER);

        add(finalPanel);
    }
}