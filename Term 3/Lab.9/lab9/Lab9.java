package lab9;

import java.awt.event.*;
import javax.swing.*;

import java.io.*;
//import java.util.*;

public class Lab9 {

    abstract class Series {

        double first;
        double step;
        int elementsDisplayed;

        public Series(double first, double step, int elementsDisplayed) {
            this.first = first;
            this.step = step;
            this.elementsDisplayed = elementsDisplayed;
        }

        abstract public double calculateElementAt(int index);

        public double calculateSumAt(int index) {
            double result = 0;
            for (int i = 1; i <= index; i++) {
                result += calculateElementAt(i);
            }
            return result;
        }

        @Override
        public String toString() {
            StringBuilder s = new StringBuilder();
            for (int i = 1; i <= elementsDisplayed; i++)
                s.append(calculateElementAt(i) + " ");
            return s.toString();
        }

        public void saveToFile(String fileName) throws IOException {
            BufferedWriter outputFile = new BufferedWriter(new FileWriter(fileName));
            outputFile.write(this.toString());
            outputFile.close();
        }

    }

    class Linear extends Series {

        public Linear(double first, double step, int elementsDisplayed) {
            super(first, step, elementsDisplayed);
        }

        @Override
        public double calculateElementAt(int index) {
            return first + step * (index - 1);
        }

    }

    class Exponential extends Series {

        public Exponential(double first, double step, int elementsDisplayed) {
            super(first, step, elementsDisplayed);
        }

        @Override
        public double calculateElementAt(int index) {
            return first * java.lang.Math.pow(step, index - 1);
        }

    }

    class Application extends JFrame {

        Series series;
        JButton generateSeries;
        JButton showSum;
        JButton outputToFile;
        JTextField firstElement;
        JTextField step;
        JTextField elementQuantity;
        JTextField outputFile;
        JTextArea seriesVisualisation;
        JTextField seriesSum;
        JComboBox<String> SeriesList;
        JRadioButton exp;
        JRadioButton lin;

        public Application() {
            super();    
            series = null;

            this.setSize(910, 420);
            this.setLayout(null);
            this.addWindowListener(new WindowAdapter()
            {
               public void windowClosing(WindowEvent e)
               {
                 dispose();
                 System.exit(0);
               }
            });

            generateSeries = new JButton("Generate series");
            outputToFile = new JButton("Output to file");
            showSum = new JButton("Show sum"); 
            generateSeries.setBounds(10, 260, 400, 40);
            outputToFile.setBounds(500, 110, 300, 40);
            showSum.setBounds(500,210,300,40);
            add(generateSeries);
            add(outputToFile);
            add(showSum);
            generateSeries.setFont(generateSeries.getFont().deriveFont(0, 20));
            outputToFile.setFont(outputToFile.getFont().deriveFont(0, 20));
            showSum.setFont(showSum.getFont().deriveFont(0,20));

            firstElement = new JTextField("Input first series element");
            step = new JTextField("Input series step");
            elementQuantity= new JTextField("Input elemenent quantity");
            outputFile = new JTextField("Input output file name");
            seriesSum = new JTextField("Sum of serie will appear here");
            firstElement.setBounds(10, 10, 400, 40);
            step.setBounds(10, 60, 400, 40);
            elementQuantity.setBounds(10, 110, 400, 40);                        
            outputFile.setBounds(500, 60, 300, 40);
            seriesSum.setBounds(500, 160, 300, 40);
            add(firstElement);
            add(step);
            add(elementQuantity);
            add(outputFile);
            add(seriesSum);
            firstElement.setFont(firstElement.getFont().deriveFont(0, 20));
            step.setFont(step.getFont().deriveFont(0, 20));
            elementQuantity.setFont(elementQuantity.getFont().deriveFont(0, 20));
            outputFile.setFont(outputFile.getFont().deriveFont(0, 20));
            seriesSum.setFont(seriesSum.getFont().deriveFont(0, 20));

            seriesVisualisation = new JTextArea("Series will appear here");
            seriesVisualisation.setBounds(10, 210, 400, 40);
            add(seriesVisualisation);
            seriesVisualisation.setFont(seriesVisualisation.getFont().deriveFont(0, 20));

            exp=new JRadioButton("Exponential");
            lin=new JRadioButton("Liner");
            
            ButtonGroup switchSeries = new ButtonGroup();
            switchSeries.add(exp);
            switchSeries.add(lin);
            exp.setSelected(true);
            lin.setBounds(10, 160, 100, 40);
            exp.setBounds(150, 160, 200, 40);
            exp.setFont(exp.getFont().deriveFont(0, 20));
            lin.setFont(lin.getFont().deriveFont(0, 20));
            
            add(exp);
            exp.setSelected(true);
            add(lin);

            setVisible(true);

            generateSeries.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent event) {
                    try {
                        double firstEl = Double.parseDouble(firstElement.getText());
                        double ratio = Double.parseDouble(step.getText());
                        int n = Integer.parseInt(elementQuantity.getText());
                        if(exp.isSelected())
                        {
                          series = new Lab9().new Exponential(firstEl, ratio, n);
                        }
                        else
                        {
                          series = new Lab9().new Linear(firstEl, ratio, n);
                        }
                      
                        seriesVisualisation.setText(series.toString());
                    } catch (Exception exception) {
                        seriesVisualisation.setText("First element and ratio must be real numbers, element quantity must be positive integer");
                        series = null;
                    }
                }
            });

            outputToFile.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent event) {
                    if(series == null) {
                        outputFile.setText("Error: Series is not defined");
                        return;                
                    }
                    try {
                        series.saveToFile(outputFile.getText());
                    } catch(Exception exception) {
                        outputFile.setText("Error: Incorrect file name");
                    }
                }
            });
            
            showSum.addActionListener(new ActionListener() {
            	public void actionPerformed(ActionEvent e) {
            		if(series == null) {
                        outputFile.setText("Error: Series is not defined");
                        return;                
                    }
            		try {
            			int n = Integer.parseInt(elementQuantity.getText());
            			double sum=series.calculateSumAt(n);
            			String result = new String();
            			seriesSum.setText(result.valueOf(sum));
            		}
            		catch(Exception exception) {
            			seriesVisualisation.setText("Element quantity must be positive integer");
            		}
            	}
            });

        }

    }

    public static void main(String[] args) throws Exception {
    	Application app = new Lab9().new Application();
    }
}