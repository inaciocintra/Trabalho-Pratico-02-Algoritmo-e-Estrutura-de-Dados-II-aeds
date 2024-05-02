import java.util.Date;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


class Personagem {

    // -----atributos personagem-----
    private String id;
    private String name;
    private ArrayList<String> alternate_names;
    private String house;
    private String ancestry;
    private String species;
    private String patronus;
    private Boolean hogwartsStaff;
    private Boolean hogwartsStudent;
    private String actorName;
    private Boolean alive;
    private Date dateOfBirth;
    private int yearOfBirth;
    private String eyeColour;
    private String gender;
    private String hairColour;
    private Boolean wizard;
    private SimpleDateFormat formatodedata = new SimpleDateFormat("dd-MM-yyyy");

    // -----contrutor sem parametros-----
    public Personagem() {
        this.id = null;
        this.name = null;
        this.alternate_names = new ArrayList<String>();
        this.house = null;
        this.ancestry = null;
        this.species = null;
        this.patronus = null;
        this.hogwartsStaff = null;
        this.hogwartsStudent = null;
        this.actorName = null;
        this.alive = null;
        this.dateOfBirth = null;
        this.yearOfBirth = 0;
        this.eyeColour = null;
        this.gender = null;
        this.hairColour = null;
        this.wizard = null;

    }

    // -----construtor-----
    public Personagem(String id, String name, ArrayList<String> alternate_names, String house, String ancestry,
            String species, String patronus, Boolean hogwartsStaff, Boolean hogwartsStudent, String actorName,
            Boolean alive, String dateOfBirth, int yearOfBirth, String eyeColour, String gender, String hairColour,
            Boolean wizard) {
        this.id = id;
        this.name = name;
        this.alternate_names = alternate_names;
        this.house = house;
        this.ancestry = ancestry;
        this.species = species;
        this.patronus = patronus;
        this.hogwartsStaff = hogwartsStaff;
        this.hogwartsStudent = hogwartsStudent;
        this.actorName = actorName;
        this.alive = alive;
        setDate(dateOfBirth);
        this.yearOfBirth = yearOfBirth;
        this.eyeColour = eyeColour;
        this.gender = gender;
        this.hairColour = hairColour;
        this.wizard = wizard;
    }

    // -----métodos gets e sets-----

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<String> getList() {

        return alternate_names;
    }

    public void setList(String todosapelidos) {
        this.alternate_names.add(todosapelidos);
    }

    public String getHouse() {
        return house;
    }

    public void setHouse(String house) {
        this.house = house;
    }

    public String getAncestry() {
        return ancestry;
    }

    public void setAncestry(String ancestry) {
        this.ancestry = ancestry;
    }

    public String getSpecies() {
        return species;
    }

    public void setSpecies(String species) {
        this.species = species;
    }

    public String getPatronus() {
        return patronus;
    }

    public void setPatronus(String patronus) {
        this.patronus = patronus;
    }

    public Boolean getHogwartsStaff() {
        return hogwartsStaff;
    }

    public void setHogwartsStaff(String condicaostaff) {
        if (condicaostaff.equals("VERDADEIRO")) {

            this.hogwartsStaff = true;
        } else {
            this.hogwartsStaff = false;
        }
    }

    public Boolean getHogwartsStudent() {
        return hogwartsStudent;
    }

    public void setHogwartsStudent(String hogwartsStudent) {
        if (hogwartsStudent.equals("VERDADEIRO")) {

            this.hogwartsStudent = true;
        } else {
            this.hogwartsStudent = false;
        }
    }

    public String getActorName() {
        return actorName;
    }

    public void setActorName(String actorName) {
        this.actorName = actorName;
    }

    public Boolean getAlive() {
        return alive;
    }

    public void setAlive(String vivo) {
        if (vivo.equals("VERDADEIRO")) {

            this.alive = true;
        } else {
            this.alive = false;
        }

    }

    public Date getDate() {
        return dateOfBirth;
    }

    public void setDate(String dataoriginal) {

        try {
            this.dateOfBirth = formatodedata.parse(dataoriginal);
        } catch (ParseException e) {
            System.out.println("Erro ao converter a data: " + e.getMessage());
        }
    }

    public int getYearOfBirth() {
        return yearOfBirth;
    }

    public void setYearOfBirth(int anoConvertido) {
        this.yearOfBirth = anoConvertido;

    }

    public String getEyeColour() {
        return eyeColour;
    }

    public void setEyeColour(String eyeColour) {
        this.eyeColour = eyeColour;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getHairColour() {
        return hairColour;
    }

    public void setHairColour(String hairColour) {
        this.hairColour = hairColour;
    }

    public Boolean getWizard() {
        return wizard;
    }

    public void setWizard(String mago) {
        if (mago.equals("VERDADEIRO")) {

            this.wizard = true;
        } else {
            this.wizard = false;
        }

    }

    // -----método clone-----
    public Personagem clone() {
        Personagem temp = new Personagem();
        temp.setYearOfBirth(this.yearOfBirth);
        temp.setName(this.name);
        return temp;
    }

    // -----método imprimir-----
    public void imprime() {
        System.out.print("[" + getId() + " ## " + getName() + " ## ");
        System.out.print("{");
        for (int i = 0; i < alternate_names.size(); i++) {
            System.out.print(alternate_names.get(i));
            if (i < alternate_names.size() - 1) {
                System.out.print(", ");
            }
        }
        System.out.print("}");
        System.out.println(" ## " + getHouse() + " ## " + getAncestry() + " ## " + getSpecies() + " ## " + getPatronus()
                + " ## " + getHogwartsStaff() + " ## " + getHogwartsStudent() + " ## " + getActorName() + " ## "
                + getAlive() + " ## " + formatodedata.format(getDate()) + " ## " + getYearOfBirth() + " ## "
                + getEyeColour() + " ## " + getGender() + " ## " + getHairColour() + " ## " + getWizard() + "]");

    }

    // -----método ler-----
    // recebe linha que vem da main
    public void ler(String linha) {
        // divide a linha ate cada ponto e virgula
        String[] dados = linha.split(";");
        if (dados.length >= 17) {
            setId(dados[0]);
            setName(dados[1]);
            // pega string dos apelidos e retira as chaves aspas e deixa somente os apelidos
            // e a virgula
            String regex = "\\s+'|\\[|\\]|\\'";
            dados[2] = dados[2].replaceAll(regex, "");
            String[] temp = dados[2].split(",");
            for (int i = 0; i < temp.length; i++) {
                setList(temp[i]);
            }
            setHouse(dados[3]);
            setAncestry(dados[4]);
            setSpecies(dados[5]);
            setPatronus(dados[6]);
            setHogwartsStaff(dados[7]);// alterar
            setHogwartsStudent(dados[8]);
            setActorName(dados[9]);
            setAlive(dados[10]);// alterar
            setDate(dados[12]);// alterar

            // alterando o ano de nascimento de string para int e chamando o set
            try {
                int anoConvertido = Integer.parseInt(dados[13]);

                setYearOfBirth(anoConvertido);// set como o ano ja em inteiro

            } catch (NumberFormatException e) {
                System.out.println("Erro ao converter a string para inteiro: " + e.getMessage());
            }

            setEyeColour(dados[14]);
            setGender(dados[15]);
            setHairColour(dados[16]);
            setWizard(dados[17]);// alterar
        }

    }
}

class Ex09 {

    public static int getMaiorFilho(int i, int tamHeap, Personagem[] nomesInseridos) {
        int filho;


        if (2 * i == tamHeap || nomesInseridos[2 * i].getHairColour().compareTo(nomesInseridos[2 * i + 1].getHairColour()) > 0) {
            filho = 2 * i; 
        } else if (nomesInseridos[2 * i].getHairColour().compareTo(nomesInseridos[2 * i + 1].getHairColour()) == 0) {
            // Se as cores de cabelo dos filhos à esquerda e à direita forem iguais, desempata comparando os nomes
            if (nomesInseridos[2 * i].getName().compareTo(nomesInseridos[2 * i + 1].getName()) > 0) {
                filho = 2 * i; 
            } else {
                filho = 2 * i + 1; 
            }
        } else {
            filho = 2 * i + 1; 
        }

        return filho;
    }


    public static void main(String[] args) {
        Personagem[] personagens = new Personagem[500];
        int j = 0;
        FileReader filereader;
        BufferedReader reader;
        Scanner entrada = new Scanner(System.in);
        String codigo;
        String nomeArquivo = "/tmp/characters.csv";

        try {

            codigo = entrada.nextLine();
            String linha;
            Boolean existe = true;

            // le a primeira linha csv e nao usa ela

            // enquanto o codigo da pub.in diferente de fim
            while (!(codigo.equals("FIM"))) {
                filereader = new FileReader(nomeArquivo);
                reader = new BufferedReader(filereader);
                reader.readLine();
                // pega a linha csv
                while ((linha = reader.readLine()) != null) {

                    // compara com a linha do csv
                    for (int i = 0; i < 32; i++) {
                        if (linha.charAt(i) != codigo.charAt(i)) {
                            existe = false;
                            i = 32;
                        } else {
                            existe = true;
                        }

                    }

                    // se o codigo/id existir no csv
                    if (existe) {
                        // cria um personagem e chama o metodo ler da classe personagem passando a linha
                        // por parametro que irá setar os atributos
                        Personagem personagem = new Personagem();
                        personagem.ler(linha);
                        personagens[j] = personagem;
                        j++;

                    }

                }
                codigo = entrada.nextLine();
                filereader.close();
                reader.close();
            }

        Personagem[] tmp = new Personagem[j+1];
        for(int i = 0; i < j; i++){
           tmp[i+1] = personagens[i];
        }
        personagens = tmp;
  
        for (int tamHeap = 2; tamHeap <= j; tamHeap++) {
            for (int i = tamHeap; i > 1; i /= 2) {
                
                if (personagens[i].getHairColour().equals(personagens[i / 2].getHairColour())) {
                    
                    if (personagens[i].getName().compareTo(personagens[i / 2].getName()) > 0) {
                        
                        
                        Personagem temp = personagens[i];
                        personagens[i] = personagens[i / 2];
                        personagens[i / 2] = temp;
                        
                    } else {
                        break; 
                    }
                } else {
                    
                    if (personagens[i].getHairColour().compareTo(personagens[i / 2].getHairColour()) > 0) {
                        
                        
                        Personagem temp = personagens[i];
                        personagens[i] = personagens[i / 2];
                        personagens[i / 2] = temp;
                        
                    } else {
                        break; 
                    }
                }
            }
        }


        
    
        
        int tamHeap = j;
        while (tamHeap > 1) {
            Personagem temp = personagens[1];
            personagens[1] = personagens[tamHeap];
            personagens[tamHeap] = temp;
            tamHeap--;
            int i = 1;
            while (i <= (tamHeap / 2)) {
                int filho = getMaiorFilho(i, tamHeap, personagens);
                if (personagens[i].getHairColour().equals(personagens[filho].getHairColour())) {
                    if (personagens[i].getName().compareTo(personagens[filho].getName()) < 0) {
                        temp = personagens[i];
                        personagens[i] = personagens[filho];
                        personagens[filho] = temp;
                        i = filho;
                    } else {
                        i = tamHeap;
                    }
                } else {
                    if (personagens[i].getHairColour().compareTo(personagens[filho].getHairColour()) < 0) {
                        temp = personagens[i];
                        personagens[i] = personagens[filho];
                        personagens[filho] = temp;
                        i = filho;
                    } else {
                        i = tamHeap;
                    }
                }
            }
        }
        tmp = personagens;
        personagens = new Personagem[j];
        for(int i = 0; i < j; i++){
           personagens[i] = tmp[i+1];
        }
            for (int i = 0; i < j; i++) {
                personagens[i].imprime();
            }
        } catch (IOException e) {
            e.printStackTrace();

        }

        entrada.close();
    }

}