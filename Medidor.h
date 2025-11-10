class Medidor {
  private:
    int id;
    String descricao;
    int status_medidor;



  public:

    Medidor() : id(0), descricao(""), status_medidor(0) {} // Construtor padrão

    Medidor(int id, String descricao, int status_medidor) {
      this->id = id;
      this->descricao = descricao;
      this->status_medidor = status_medidor;
    }


    int getId() {
      return this->id;
    }

    String getDescricao() {
      return this->descricao;
    }

    int getStatus() {
      return this->status_medidor;
    }

};
