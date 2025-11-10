APRIMORANDO A EFICIENCIA NA PECUARIA LEITEIRA: MONITORAMENTO REMOTO DE MEDIDORES ELETRONICOS COM IOT 



Abstract⎯   This article introduces a system designed to collect data from digital electronic milk meters on dairy farms, employing Internet of Things (IoT) technology. The system aims to provide intuitive access to both general and individual production data, empowering producers to enhance operational efficiency and ensure animal welfare. By leveraging IoT capabilities, this system grants streamlined access to precise data, enabling comprehensive analyses essential for optimizing dairy production. 
Keywords⎯   Electronic meters, Internet of Things (IoT), Dairy production, Remote monitoring, Data analysis, Agricultural management, Technology in livestock. 
Resumo⎯   O artigo apresenta um sistema de coleta de dados de medidores eletrônicos digitais em fazendas leiteiras, utilizando a Internet das Coisas (IoT). Através dessa tecnologia, disponibiliza de forma intuitiva informações gerais e individuais da produção, visando melhorar a eficiência operacional e o bem-estar dos animais. Este sistema proporciona aos produtores acesso facilitado a dados precisos, permitindo análises abrangentes e específicas para otimização da produção leiteira. 
Palavras-chave⎯ Medidores eletrônicos, internet das coisas (IoT), produção leiteira, monitoramento remoto, análise de dados, gestão agropecuária, tecnologia na pecuária.  
 
 
 
	1 	Introdução 
A pecuária leiteira é um dos pilares da agricultura brasileira, representando uma importante fonte de renda e sustento para milhares de produtores em todo o país. De acordo com dados do Instituto Brasileiro de Geografia e Estatística (IBGE), em 2020, o Brasil ocupava o quarto lugar no ranking mundial de produção de leite, com uma produção de aproximadamente 34,7 bilhões de litros anuais. Além disso, a pecuária leiteira emprega um grande contingente de trabalhadores rurais e contribui significativamente para a economia nacional. No entanto, por trás desses números impressionantes, existe um desafio persistente que afeta a eficiência e a rentabilidade da indústria leiteira no Brasil: a falta de gestão e controle de dados eficaz. Embora o país seja um dos principais produtores de leite do mundo, muitos produtores ainda operam com métodos tradicionais de ordenha e gestão de rebanhos, muitas vezes negligenciando a implementação de soluções tecnológicas avançadas que poderiam melhorar a produtividade e a qualidade do leite. A ausência de sistemas de monitoramento adequados e a falta de informações em tempo real sobre a produção leiteira resultam em ineficiências significativas, desperdício de recursos e perdas econômicas para os produtores. A gestão de dados é uma parte crucial do processo de produção, permitindo o acompanhamento preciso da saúde dos animais, a qualidade do leite, a detecção precoce de problemas de produção e a tomada de decisões informadas. No entanto, a pecuária leiteira no Brasil muitas vezes opera com sistemas desconexos e processos manuais, tornando difícil atender às demandas crescentes por qualidade e sustentabilidade. 
Neste contexto, a Internet das Coisas (IoT) emerge como uma solução promissora, permitindo a automação e o monitoramento de diversas etapas da produção leiteira. A aplicação de sensores e dispositivos conectados pode revolucionar a forma como os produtores gerenciam seus rebanhos, permitindo um controle mais eficiente e uma gestão de dados em tempo real. Este trabalho de conclusão de curso tem como objetivo explorar o potencial da IoT na pecuária leiteira brasileira, propondo um sistema de ordenha eletrônica que controla o volume de leite produzido por cada animal e envia esses dados para um site central, proporcionando aos produtores informações precisas para aprimorar a gestão de seus rebanhos e, consequentemente, otimizar a produção de leite no país. 
	2 	Recomendações 
2.1 	Elementos textuais 
A Internet das Coisas (IoT) revolucionou a maneira como objetos e dispositivos se comunicam e interagem entre si, oferecendo inúmeras aplicações em diferentes setores, como agricultura, saúde, automação residencial e muito mais. Para habilitar essa revolução, é crucial contar com componentes eletrônicos robustos e versáteis. Este trabalho explora a relevância e as características dos componentes eletrônicos NodeMCU, ESP32 e Arduino na implementação de projetos de IoT. 
O NodeMCU é uma plataforma de desenvolvimento IoT que utiliza o microcontrolador ESP8266. O NodeMCU combina a capacidade de conectividade Wi-Fi embutida do ESP8266 com a facilidade de programação através da linguagem Lua. Isso torna a NodeMCU uma escolha popular para iniciantes em IoT. Alguns pontos-chave a serem observados incluem: 
 
-	Conectividade Wi-Fi: O NodeMCU é conhecido por sua conectividade Wi-Fi integrada, permitindo que dispositivos se comuniquem com a Internet e outros dispositivos em uma rede local. 
 
-	Facilidade de Programação: A NodeMCU é programada em Lua, uma linguagem de script de alto nível que é relativamente fácil de aprender e usar. 
 
-	Comunidade Ativa: A plataforma NodeMCU possui uma comunidade ativa de desenvolvedores e uma vasta quantidade de recursos, bibliotecas e tutoriais disponíveis online. 
 
O	ESP32 é uma plataforma de desenvolvimento IoT que se baseia no ESP8266, mas oferece ainda mais recursos e desempenho. É notável por sua conectividade Wi-Fi e 
Bluetooth, tornando-o adequado para aplicações IoT que exigem comunicação sem fio robusta. Alguns aspectos importantes incluem: 
 
-	Conectividade Dual: O ESP32 suporta Wi-Fi e Bluetooth, o que permite uma ampla gama de aplicações IoT, desde sensores sem fio até dispositivos de automação residencial. 
 
-	Desempenho Aprimorado: O ESP32 é mais poderoso que o ESP8266, com mais memória e capacidade de processamento, tornando-o adequado para tarefas mais complexas. 
 
-	Suporte à Programação em C/C++:O ESP32 é frequentemente programado usando a IDE do Arduino, o que simplifica a criação de projetos. 
  
O	Arduino é uma plataforma de desenvolvimento eletrônico amplamente utilizada que se tornou uma escolha popular para projetos de IoT devido à sua simplicidade e versatilidade. O Arduino pode ser combinado com módulos de comunicação, como o ESP8266 ou o ESP32, para habilitar a conectividade IoT. Alguns pontos de destaque incluem: 
 
-	Comunidade Ativa: O Arduino tem uma comunidade global ativa, com uma ampla variedade de recursos e bibliotecas disponíveis para suportar projetos IoT. 
-	Facilidade de Programação: A linguagem de programação do Arduino é baseada em C/C++, e sua IDE é amigável para iniciantes. 
-	Integração com Módulos IoT: O Arduino pode ser estendido com módulos de comunicação, como o ESP8266 ou o ESP32, para habilitar a conectividade Wi-Fi e Bluetooth. Em resumo, o NodeMCU, o ESP32 e o Arduino são componentes eletrônicos cruciais para o desenvolvimento de projetos de IoT. Cada um tem suas próprias características e vantagens, tornando-os adequados para diferentes aplicações e níveis de experiência. A escolha do componente depende das necessidades específicas do projeto e do nível de familiaridade do desenvolvedor com a plataforma.  	O medidor de leite eletrônico com painel digital é uma ferramenta valiosa disponível no mercado para produtores de leite. Este dispositivo foi projetado para facilitar a medição precisa do volume de leite produzido por cada animal durante o processo de ordenha. O painel digital fornece uma interface intuitiva que exibe os dados de produção, permitindo que os produtores monitorem a eficiência da ordenha e tomem decisões informadas. 
 
Características típicas desse medidor incluem: 
 
1.	Display Digital: O painel digital oferece uma leitura clara e fácil de entender do volume de leite produzido. 
 
2.	Medição Precisa: O dispositivo é projetado para garantir uma medição precisa do volume de leite, minimizando erros humanos e fornecendo dados confiáveis. 
 
3.	Durabilidade: Esses medidores são construídos para suportar as condições adversas de uma fazenda leiteira, incluindo um ambiente úmido e propenso a respingos de leite. 
 
4.	Alimentação Elétrica: Em muitos casos, o dispositivo é alimentado por uma fonte de energia, garantindo seu funcionamento durante a ordenha. 
 
Embora esse medidor de leite eletrônico seja eficaz para fornecer aos produtores informações essenciais sobre a 
 
produção de leite, é importante observar que ele não oferece conectividade à internet. Portanto, os dados de produção não são enviados automaticamente para um sistema online para análise posterior. No entanto, a capacidade de visualizar os dados durante o processo de ordenha ainda representa um avanço significativo em comparação com métodos manuais de medição, auxiliando os produtores na gestão de seu rebanho e no aumento da eficiência da produção leiteira. 
 
 
Realizando um estudo em laboratório com o auxílio de um osciloscópio, foi possível observar o funcionamento dos medidores de leite. Esses dispositivos operam com sensores alimentados por uma tensão de 5V de corrente contínua. Durante as análises, ficou evidente que quando os sensores detectavam a presença de leite em sua área de medição, a saída desses sensores apresentava uma tensão de 0V. 
 
Essa característica é fundamental para o funcionamento preciso dos medidores, pois a mudança de 5V para 0V indica claramente o momento em que o leite é detectado, permitindo que os medidores registrem e calculem a quantidade de leite produzida com precisão.  
 
  
 
 
	3 	Hardwares 
 
O desenvolvimento do hardware para este projeto envolveu a implementação de dois componentes distintos e complementares. O primeiro componente consiste em uma unidade central responsável por conectar, via cabo, o sensor do medidor eletrônico ao microcontrolador Arduino. Essa unidade é essencial para a coleta precisa dos dados relativos à produção de leite durante o processo de ordenha. O segundo hardware é um módulo baseado em ESP32, cuja função é permitir a identificação dos animais durante a ordenha. Essa identificação é crucial para associar os dados de produção de leite a cada animal individualmente, possibilitando uma gestão mais precisa e personalizada do rebanho. A combinação desses dois componentes desempenha um papel fundamental no sucesso deste projeto, garantindo uma coleta de dados precisa e fornecendo informações essenciais para a eficiência da produção leiteira. 
 
 
  
3.1 Central  
O hardware da central desempenha um papel fundamental no projeto de monitoramento e controle de produção de leite eletrônico, possibilitando a coleta, processamento e transmissão de dados essenciais. Esta central é composta por dois componentes-chave: um Arduino Uno e um NodeMCU, cada um com funções distintas e complementares. 
 
-	Arduino Uno: O Arduino Uno é o coração da central, responsável por coletar e processar os dados provenientes dos medidores eletrônicos. Neste sistema, quatro medidores eletrônicos estão interconectados com o Arduino Uno. Os sensores magnéticos de cada medidor são conectados aos pinos digitais D2 a D5 do Arduino, permitindo a leitura precisa da produção de leite em tempo real. Além disso, botões de reinicialização de ordenha estão conectados aos pinos D6 a D9 do Arduino, fornecendo a funcionalidade de reiniciar o processo de ordenha para o próximo animal. Isso é crucial para garantir a separação dos dados de produção de leite de cada animal. 
-	NodeMCU: O NodeMCU é responsável por enviar os dados coletados para a nuvem, permitindo o acesso remoto e a análise dos dados. Ele está conectado aos pinos D11 e D12 do Arduino, garantindo a transmissão confiável dos dados coletados. A escolha do NodeMCU para a transmissão de dados é devida à sua capacidade de conectividade Wi-Fi, tornando-o adequado para enviar informações para um servidor na nuvem, onde podem ser armazenadas e acessadas remotamente. 
Conexão GND: Para garantir o correto funcionamento da central e evitar potenciais problemas de aterramento, o Arduino Uno e o NodeMCU compartilham o mesmo ponto de aterramento (GND), criando uma referência comum para o sistema. Isso é importante para evitar variações de potencial elétrico e garantir uma operação estável e confiável. 
 
O hardware da central, com o uso do Arduino Uno e do NodeMCU, permite uma integração eficaz dos dados de produção de leite dos medidores eletrônicos e sua transmissão para a nuvem. Isso proporciona um sistema de monitoramento completo e moderno que auxilia os produtores na gestão da produção leiteira, oferecendo acesso 
a informações em tempo real e facilitando a tomada de decisões informadas para otimizar o processo de ordenha. 
  
3.2 Hardware de identificação 
No contexto do sistema de monitoramento da produção de leite eletrônico, foi desenvolvido um hardware de identificação animal para associar dados de produção de leite a animais específicos. Esse componente desempenha um papel fundamental na rastreabilidade e na gestão individualizada dos animais durante o processo de ordenha. O hardware de identificação animal é composto por vários elementos essenciais, incluindo: 
-	Leitor de RFID Sem Fio: Um leitor de RFID (Identificação por Radiofrequência) passivo sem fio é o componente principal deste hardware. Ele é projetado para detectar etiquetas RFID inseridas nos animais, permitindo a identificação única de cada um. Quando um animal se aproxima do leitor de RFID, a etiqueta em seu corpo é detectada, fornecendo informações cruciais sobre sua identidade. 
-	ESP32: O hardware de identificação animal é alimentado por um microcontrolador ESP32. O ESP32 é responsável por gerenciar a comunicação com o leitor de RFID, bem como por processar e exibir os dados na tela LCD. Além disso, o ESP32 se conecta à rede Wi-Fi para transmitir as informações identificadas para o NodeMCU, que por sua vez, envia os dados para a nuvem. 
A integração do leitor de RFID com o ESP32 e a 
tela LCD possibilita a identificação precisa de cada animal durante a ordenha. Quando um animal se aproxima do sistema, o leitor de RFID captura a identificação única do animal, o ESP32 processa essa informação e a exibe na tela LCD. Através da comunicação Wi-Fi, esses dados são então transmitidos para o NodeMCU, que centraliza as informações de todos os animais e as envia para a nuvem, onde podem ser acessadas e analisadas remotamente. Essa abordagem proporciona uma gestão eficaz da produção leiteira, garantindo o registro e a monitorização individualizada de cada animal durante o processo de ordenha. 
  
 
 
	4 	Desenvolvimento Web e banco de dados 
 
Para possibilitar uma gestão eficaz e acessível dos dados coletados a partir do sistema de monitoramento de produção de leite eletrônico, foi desenvolvida uma plataforma web hospedada na plataforma Netlify, com o domínio "fazendachale.netlify.app". Esta plataforma foi concebida com a finalidade de fornecer uma interface intuitiva e eficiente para os produtores, de forma a otimizar a gestão do rebanho e da produção leiteira. 
A plataforma consiste em quatro principais páginas: 
 
1.	Página Inicial: Nesta página, os produtores podem visualizar, em tempo real, o status dos medidores eletrônicos, indicando se estão ativos ou inativos. Essa informação é crucial para garantir a funcionalidade do sistema de ordenha. 
2.	Animais Cadastrados: A segunda página lista todos os animais cadastrados, apresentando informações como o brinco e o número da tag RFID associados a cada animal. Essa seção facilita o gerenciamento individualizado de cada animal na fazenda. 
3.	Cadastro de Tags RFID: Uma página dedicada permite o cadastro de novas tags RFID, tornando o processo de inclusão de novos animais no sistema simples e prático. 
4.	Histórico de Ordenhas: A página oferece um histórico detalhado das ordenhas realizadas, com a capacidade de filtrar as informações com base em diversos critérios, permitindo uma análise aprofundada da produção ao longo do tempo. 
5.	Graficos: Esta aba oferece uma representação visual e mais intuitiva do histórico de pesagem do leite de cada animal na fazenda. Ao apresentar os dados de produção de forma gráfica, essa funcionalidade permite uma análise mais acessível e simplificada para o usuário da plataforma.  
Essa plataforma web foi projetada para fornecer uma solução abrangente e de fácil utilização, permitindo que os produtores acessem e analisem os dados de produção de leite eletrônico de maneira eficiente. A comunicação contínua entre o hardware e a plataforma web possibilita o acesso em tempo real a 
informações críticas, o que, por sua vez, contribui para uma gestão mais eficaz e uma produção leiteira mais eficiente na fazenda. 
 
 
 
 
 
 
O presente estudo se concentra na análise de uma implementação web hospedada na plataforma Netlify, desenvolvida utilizando um conjunto de tecnologias e ferramentas de vanguarda. Estas ferramentas desempenham papéis fundamentais no desenvolvimento e implantação de aplicativos da web modernos. A implementação em questão é composta por: 
 
1.	**Netlify**: Netlify é uma plataforma de hospedagem e automação reconhecida por sua capacidade de simplificar o processo de hospedagem de sites e aplicativos da web. Ela oferece integração contínua, implantação contínua (CI/CD), e outros recursos essenciais, incluindo segurança com HTTPS gratuito e escalabilidade eficiente. 
2.	**React JS**: React JS é uma biblioteca JavaScript amplamente adotada para o desenvolvimento de interfaces de usuário dinâmicas. Por meio do conceito de componentização, React possibilita a criação de elementos de interface reutilizáveis e facilita a construção de interfaces interativas. 
3.	**JavaScript**: A linguagem de programação JavaScript desempenha um papel central na implementação, proporcionando a funcionalidade de programação do lado do cliente. Ela é usada para criar uma experiência de usuário dinâmica, melhorando a interatividade e a capacidade de resposta do aplicativo da web. 
4.	**Java Spring Boot**: O framework Java Spring Boot é empregado no lado do servidor para gerenciar a lógica de negócios do aplicativo. Ele simplifica o desenvolvimento de aplicativos da web, fornecendo configurações fáceis de implementar e abstraindo detalhes técnicos complexos. 
5.	**MySQL**: O sistema de gerenciamento de banco de dados relacional MySQL é utilizado para armazenar e recuperar dados de maneira estruturada. Sua aplicação é fundamental para garantir a persistência e confiabilidade dos dados em aplicativos da web. 
A integração destas tecnologias oferece um ambiente de desenvolvimento completo, capaz de criar, implantar e manter aplicativos web sofisticados. A escolha da plataforma Netlify como host simplifica significativamente o processo de implantação e gerenciamento do site, permitindo uma abordagem mais eficiente e escalável ao desenvolvimento web moderno. 
 
	5 	Resultados 
 
O sistema de monitoramento de produção em uma fazenda de produção leiteira localizada na cidade de Jesuânia, MG. A fazenda, que já possuía um sistema de ordenha mecanizado, ofereceu condições ideais para a instalação e integração do sistema de monitoramento. A implementação do sistema ocorreu no mês de novembro, marcando o início da coleta de dados de produção de leite na fazenda. 
Durante a fase inicial de implantação, o sistema foi configurado para coletar dados de produção de leite de três animais específicos da fazenda. Essa abordagem permitiu uma análise e testes iniciais do funcionamento do sistema em um ambiente real de produção. A escolha estratégica de iniciar com um número limitado de animais facilitou a validação do sistema, permitindo ajustes e otimizações necessárias para garantir seu correto funcionamento e eficiência. 
A fazenda, com seu sistema de ordenha mecanizado existente, ofereceu a infraestrutura necessária para a integração perfeita do sistema de monitoramento. A capacidade de adaptar e instalar o hardware em um ambiente já estruturado de produção de leite foi fundamental para o sucesso inicial do projeto. A coleta de dados dos três animais representou o primeiro passo significativo na implementação e validação do sistema, sinalizando o potencial para uma gestão mais eficiente e detalhada da produção leiteira na fazenda. 
De acordo com o protocolo estabelecido, os animais acompanhados durante as ordenhas foram identificados através de brincos de identificação animal, os quais foram associados a tags RFID específicas. A associação entre os brincos de identificação e suas respectivas tags RFID é detalhada na tabela abaixo:  
 
Animal 	Brinco de identificação 	Tag RFID 
1 	506 	12047841169 
2 	614 	74512134785 
3 	1474 	447952123545 
 
De maneira abrangente, a análise dos dados coletados durante o mês de novembro permitiu constatar que, coletivamente, os animais monitorados apresentaram uma produção de aproximadamente 2 mil litros de leite. Esse resultado representa a soma dos volumes individuais de produção de leite dos animais durante o período mencionado, evidenciando a contribuição conjunta desses animais para a produção leiteira ao longo do mês de monitoramento. Este dado agregado é relevante para compreender a produtividade coletiva dos animais acompanhados durante o período determinado, fornecendo uma visão geral do desempenho da produção leiteira neste intervalo de tempo. 
Durante a análise individualizada e acompanhamento dos animais, observou-se divergências significativas na produção de dois animais em dias específicos. O animal identificado pelo brinco 1474 registrou uma queda acentuada de mais de 50% em sua produção habitual no dia 16 de novembro. Esta variação atípica despertou atenção e, em conjunto com a avaliação de um veterinário especializado, identificou-se uma inflamação no casco do animal. A pronta detecção dessa condição permitiu o início imediato de um tratamento preventivo para a inflamação, visando a recuperação e o bem-estar do animal. 
  
Outra observação relevante foi referente ao animal identificado pelo brinco 614, que apresentou uma significativa queda em sua produção no dia 19 de novembro. A análise em conjunto com profissionais especializados revelou que o animal estava no período de cio. Diante disso, logo em seguida, foi possível realizar a inseminação artificial do animal, contribuindo para o planejamento reprodutivo e potencializando a eficiência do processo de reprodução na fazenda. Essa pronta identificação e intervenção demonstraram a importância do monitoramento individualizado dos animais, possibilitando a detecção precoce de problemas de saúde e a implementação de medidas corretivas e preventivas adequadas para garantir o bemestar e a produtividade do rebanho. 
  
 
 
 
 
 
	6 	Conclusão 
 
O presente Trabalho de Conclusão de Curso (TCC) revelou-se fundamental ao apresentar e implementar um sistema funcional de monitoramento de produção de leite eletrônico em uma fazenda. Este projeto demonstrou-se não apenas viável, mas também ofereceu benefícios significativos tanto para a gestão da produção leiteira quanto para o bem-estar dos animais. 
 
De maneira geral, o sistema desenvolvido proporcionou ao produtor uma ferramenta de controle remoto da produção, viabilizando o acompanhamento mesmo à distância. Essa capacidade de monitoramento remoto permite ao produtor tomar decisões informadas e estratégicas, contribuindo para uma gestão mais eficaz da produção, independentemente da sua presença física na fazenda. 
 
Além disso, a implementação do sistema revelou-se benéfica para o bem-estar animal, uma vez que possibilitou a identificação precoce de problemas de saúde ou comportamentais. A detecção de variações na produção individual de leite, como aquelas observadas nos casos dos animais com brincos 1474 e 614, permitiu ações imediatas, como tratamentos preventivos e identificação de cio, resultando em um cuidado mais personalizado e proativo em relação aos animais. 
 
A análise individualizada da produtividade de cada animal, bem como a precisão na identificação do cio, evidenciou a eficiência do sistema no gerenciamento da produção leiteira. Essa abordagem direcionada possibilita a implementação de medidas específicas para otimizar a produção e a saúde dos animais, resultando em uma operação mais eficiente e rentável na fazenda. 
 
Em resumo, o sistema de monitoramento de produção de leite eletrônico revelou-se uma ferramenta valiosa e multifuncional. Sua capacidade de proporcionar controle remoto, cuidados direcionados aos animais e análises individualizadas da produção demonstra um potencial significativo para melhorias na gestão de fazendas leiteiras, contribuindo para um ambiente mais sustentável, eficiente e 
benéfico para produtores e animais. 
Referências 
**Referências NodeMCU:** 
 
1.	Official NodeMCU Website: https://nodemcu.readthedocs.io/ 
2.	"Getting Started with NodeMCU" - Instructables: https://www.instructables.com/id/Getting-Started-With-
NodeMCU-ESP8266-on-Arduino-IDE/ 3. "NodeMCU Documentation" - GitHub: https://github.com/nodemcu/nodemcu-firmware 
 
**Referências ESP32:** 
 
1.	Official ESP32 Documentation: https://docs.espressif.com/projects/espidf/en/latest/esp32/index.html 
 
2.	"Getting Started with ESP32" - Espressif Systems: 
https://docs.espressif.com/projects/espidf/en/latest/esp32/get-started/index.html 3. "Introduction to ESP32" - Arduino: https://www.arduino.cc/en/Guide/ESP32 
 
 
**Referências Arduino:** 
 
1. Official Arduino Website: https://www.arduino.cc/ 2. "Arduino Reference" - Arduino: https://www.arduino.cc/reference/en/ 3. "Arduino for Beginners" - Instructables: 
https://www.instructables.com/class/Arduino-Class/ 
 
 
