-- Database created to illustrate a snapshot of a football championship

DROP SCHEMA IF EXISTS Geral CASCADE;
CREATE SCHEMA Geral;
SET SCHEMA 'Geral';

DROP TABLE IF EXISTS tb_jgd_Jogador CASCADE;
CREATE TABLE tb_jgd_Jogador (
	num_Registro_pk SERIAL PRIMARY KEY,
	str_Nome_jgd VARCHAR(30) NOT NULL,
	str_CPF_jgd CHAR(11) NULL UNIQUE,
	str_Email_jgd VARCHAR(50) NOT NULL,
	str_Telefone_jgd VARCHAR(12) NOT NULL,
	date_Data_de_Nascimento DATE NOT NULL,
	str_Posição VARCHAR(30) NOT NULL
);

COMMENT ON TABLE tb_jgd_Jogador IS 'Jogadores Cadastrados';
COMMENT ON	COLUMN tb_jgd_Jogador.num_Registro_pk IS 'Registro Serial para identificação do Jogador';
COMMENT ON	COLUMN tb_jgd_Jogador.str_Nome_jgd IS 'Nome Completo do Jogador';
COMMENT ON	COLUMN tb_jgd_Jogador.str_CPF_jgd IS 'CPF dos jogadores maiores de idade';
COMMENT ON	COLUMN tb_jgd_Jogador.str_Email_jgd IS 'Email do Jogador';
COMMENT ON	COLUMN tb_jgd_Jogador.str_Telefone_jgd IS 'Telefone do Jogador';
COMMENT ON	COLUMN tb_jgd_Jogador.date_Data_de_Nascimento IS 'Data de Nascimento do Jogador';
COMMENT ON	COLUMN tb_jgd_Jogador.str_Posição IS 'Posição que joga em campo';

DROP TABLE IF EXISTS tb_tec_Técnico CASCADE;
CREATE TABLE tb_tec_Técnico (
	str_CPF_pk CHAR(11) PRIMARY KEY,
	str_Nome_tec VARCHAR(30) NOT NULL,
	str_Email_tec VARCHAR(50) NOT NULL,
	str_Telefone_tec VARCHAR(12) NOT NULL,
	str_Especialidade VARCHAR(30) NOT NULL
);

COMMENT ON TABLE tb_tec_Técnico IS 'Técnicos Cadastrados';
COMMENT ON	COLUMN tb_tec_Técnico.str_CPF_pk IS 'CPF para identificação dos Técnicos';
COMMENT ON	COLUMN tb_tec_Técnico.str_Nome_tec IS 'Nome Completo do Técnico';
COMMENT ON	COLUMN tb_tec_Técnico.str_Email_tec IS 'Email do Técnico';
COMMENT ON	COLUMN tb_tec_Técnico.str_Telefone_tec IS 'Telefone do Técnico';
COMMENT ON	COLUMN tb_tec_Técnico.str_Especialidade IS 'Caracterítica do Técnico ex: Principal, Auxiliar...';

DROP TABLE IF EXISTS tb_clu_Clube CASCADE;
CREATE TABLE tb_clu_Clube (
	str_CNPJ_pk CHAR(14) PRIMARY KEY,
	str_Nome_clu VARCHAR(30) NOT NULL,
	str_UF CHAR(2) NOT NULL,
	int_Ano_Fundação INTEGER NOT NULL,
	str_CPF_Técnico_fk CHAR(11) NULL,
    FOREIGN KEY (str_CPF_Técnico_fk) REFERENCES tb_tec_Técnico (str_CPF_pk)
);

ALTER TABLE tb_clu_Clube
	ADD CONSTRAINT ck_clu_ano_inválido
		CHECK (int_Ano_Fundação >= 1500 AND int_Ano_Fundação <= 3000); 

COMMENT ON TABLE tb_clu_Clube IS 'Clubes Cadastrados';
COMMENT ON	COLUMN tb_clu_Clube.str_CNPJ_pk IS 'CNPJ para identificação dos Clubes';
COMMENT ON	COLUMN tb_clu_Clube.str_Nome_clu IS 'Nome do Clube';
COMMENT ON	COLUMN tb_clu_Clube.str_UF IS 'Região do Brasil, com sigla de 2 letras, com a localização do Clube';
COMMENT ON	COLUMN tb_clu_Clube.int_Ano_Fundação IS 'Ano de Fudação do Clube';
COMMENT ON	COLUMN tb_clu_Clube.str_CPF_Técnico_fk IS 'Chave Estrangeira para o CPF do Técnico do Clube';

DROP TABLE IF EXISTS tb_cam_Campeonato CASCADE;
CREATE TABLE tb_cam_Campeonato (
	num_Id_pk SERIAL PRIMARY KEY,
	str_Nome_cam VARCHAR(30) NOT NULL,
	int_Ano_cam INTEGER NOT NULL,
	str_CNPJ_Campeão_fk CHAR(14) NOT NULL,
    FOREIGN KEY (str_CNPJ_Campeão_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk),
    int_Premiação INTEGER NULL
);

ALTER TABLE tb_cam_Campeonato
	ADD CONSTRAINT ck_cam_ano_inválido
		CHECK (int_Ano_cam >= 1500 AND int_Ano_cam <= 3000); 

ALTER TABLE tb_cam_Campeonato
	ADD CONSTRAINT ck_cam_premiação_inválida
		CHECK (int_Premiação >= 1 AND int_Premiação <= 100000000); 

COMMENT ON TABLE tb_cam_Campeonato IS 'Campeonatos Cadastrados';
COMMENT ON	COLUMN tb_cam_Campeonato.num_Id_pk IS 'Id serial para identificação dos Campeonatos';
COMMENT ON	COLUMN tb_cam_Campeonato.str_Nome_cam IS 'Nome do Campeonato';
COMMENT ON	COLUMN tb_cam_Campeonato.int_Ano_cam IS 'Ano de realização de certo Campeonato';
COMMENT ON	COLUMN tb_cam_Campeonato.str_CNPJ_Campeão_fk IS 'Chave Estrangeira para o CNPJ do Clube que ganhou determinado Campeonato';
COMMENT ON	COLUMN tb_cam_Campeonato.int_Premiação IS 'Premiação dada ao campeão do Campeonato (pode ser nula)';

DROP TABLE IF EXISTS tb_dis_Disputa CASCADE;
CREATE TABLE tb_dis_Disputa (
	str_CNPJ_pk_fk CHAR(14),
	int_Id_pk_fk INTEGER,
	PRIMARY KEY (str_CNPJ_pk_fk, int_Id_pk_fk),
	FOREIGN KEY (str_CNPJ_pk_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk),
	FOREIGN KEY (int_Id_pk_fk) REFERENCES tb_cam_Campeonato (num_Id_pk),
	int_Pontuação INTEGER NULL,
    int_Colocação INTEGER NOT NULL
);

ALTER TABLE tb_dis_Disputa
	ADD CONSTRAINT ck_dis_pontuação_inválida
		CHECK (int_Pontuação >= 1 AND int_Pontuação <= 100); 

ALTER TABLE tb_dis_Disputa
	ADD CONSTRAINT ck_dis_colocação_inválida
		CHECK (int_Colocação >= 1 AND int_Colocação <= 50); 

COMMENT ON TABLE tb_dis_Disputa IS 'Relação dos Clubes que disputam Campeonatos';
COMMENT ON	COLUMN tb_dis_Disputa.str_CNPJ_pk_fk IS 'Chave Estrangeira para o CNPJ de identificação do Clube';
COMMENT ON	COLUMN tb_dis_Disputa.int_Id_pk_fk IS 'Chave Estrangeira para o Id de identificação do Campeonato';
COMMENT ON	COLUMN tb_dis_Disputa.int_Pontuação IS 'Pontuação de certo Clube nesse Campeonato (pode ser nula)';
COMMENT ON	COLUMN tb_dis_Disputa.int_Colocação IS 'Colocação de certo Clube nesse Campeonato';

DROP TABLE IF EXISTS tb_est_Estádio CASCADE;
CREATE TABLE tb_est_Estádio (
    num_Id_Estádio_pk SERIAL PRIMARY KEY,
	str_Nome_est VARCHAR(30) NOT NULL,
	str_UF CHAR(2) NOT NULL,
	int_Capacidade INTEGER NOT NULL,
	str_CNPJ_Dono_fk CHAR(14) NULL,
    FOREIGN KEY (str_CNPJ_Dono_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk)
);

ALTER TABLE tb_est_Estádio
	ADD CONSTRAINT ck_est_capacidade_inválida
		CHECK (int_Capacidade >= 1 AND int_Capacidade <= 100000);

COMMENT ON TABLE tb_est_Estádio IS 'Estádios Cadastrados';
COMMENT ON	COLUMN tb_est_Estádio.num_Id_Estádio_pk IS 'Id serial para identificação dos Estádios';
COMMENT ON	COLUMN tb_est_Estádio.str_Nome_est IS 'Nome do Estádio';
COMMENT ON	COLUMN tb_est_Estádio.str_UF IS 'Região do Brasil, com sigla de 2 letras, com a localização do Estádio';
COMMENT ON	COLUMN tb_est_Estádio.int_Capacidade IS 'Capacidade total de pessoas que cabem no Estádio';
COMMENT ON	COLUMN tb_est_Estádio.str_CNPJ_Dono_fk IS 'Chave Estrangeira para o CNPJ do Clube que é dono do Estádio (pode não ter dono)';

DROP TABLE IF EXISTS tb_jga_Joga CASCADE;
CREATE TABLE tb_jga_Joga (
	int_Registro_pk_fk INTEGER,
	str_CNPJ_pk_fk CHAR(14),
    PRIMARY KEY (int_Registro_pk_fk, str_CNPJ_pk_fk),
	FOREIGN KEY (int_Registro_pk_fk) REFERENCES tb_jgd_Jogador (num_Registro_pk),
    FOREIGN KEY (str_CNPJ_pk_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk),
	str_Elenco VARCHAR(30) NOT NULL
);

COMMENT ON TABLE tb_jga_Joga IS 'Relação dos Jogadores com os Clubes que eles jogam';
COMMENT ON	COLUMN tb_jga_Joga.int_Registro_pk_fk IS 'Chave Estrangeira para o Registro Serial de um Jogador';
COMMENT ON	COLUMN tb_jga_Joga.str_CNPJ_pk_fk IS 'Chave Estrangeira para o CNPJ do Clube que contrata o Jogador';
COMMENT ON	COLUMN tb_jga_Joga.str_Elenco IS 'Elenco que o jogador está situado ex: Sub-20, reserva, titular';


DROP TABLE IF EXISTS tb_par_Partida CASCADE;
CREATE TABLE tb_par_Partida (
	str_Mandante_pk_fk CHAR(14),
	str_Visitante_pk_fk CHAR(14),
	int_Id_Estádio_pk_fk INTEGER,
	int_Campeonato_pk_fk INTEGER,
	date_Data_pk DATE,
	str_Vitorioso_fk CHAR(14) NULL,
	PRIMARY KEY (str_Mandante_pk_fk, str_Visitante_pk_fk, int_Id_Estádio_pk_fk, int_Campeonato_pk_fk, date_Data_pk),
	FOREIGN KEY (str_Mandante_pk_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk),
    FOREIGN KEY (str_Visitante_pk_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk),
    FOREIGN KEY (int_Id_Estádio_pk_fk) REFERENCES tb_est_Estádio (num_Id_Estádio_pk),
    FOREIGN KEY (int_Campeonato_pk_fk) REFERENCES tb_cam_Campeonato (num_Id_pk),
    FOREIGN KEY (str_Vitorioso_fk) REFERENCES tb_clu_Clube (str_CNPJ_pk),
	int_Gols_Mandante INTEGER NOT NULL,
	int_Gols_Visitante INTEGER NOT NULL    
);

ALTER TABLE tb_par_Partida
	ADD CONSTRAINT ck_par_gols_mandante_max
		CHECK (int_Gols_Mandante <= 20); 

ALTER TABLE tb_par_Partida
	ADD CONSTRAINT ck_par_gols_visitante_max
		CHECK (int_Gols_Visitante <= 20); 

ALTER TABLE tb_par_Partida
	ADD CONSTRAINT ck_par_empate_nao_tem_vencedor
		CHECK(int_Gols_Mandante <> int_Gols_Visitante
				OR str_Vitorioso_fk IS NULL);


COMMENT ON TABLE tb_par_Partida IS 'Relação dos dois times que jogam uma partida em um Estádio por certo Campeonato na data determinada';
COMMENT ON	COLUMN tb_par_Partida.str_Mandante_pk_fk IS 'Chave Estrangeira para o CNPJ do Clube dono do Estádio (Mandante)';
COMMENT ON	COLUMN tb_par_Partida.str_Visitante_pk_fk IS 'Chave Estrangeira para o CNPJ do Clube jogando fora de casa (Visitante)';
COMMENT ON	COLUMN tb_par_Partida.int_Id_Estádio_pk_fk IS 'Chave Estrangeira para o Id do Estádio que a partida é disputada';
COMMENT ON	COLUMN tb_par_Partida.int_Campeonato_pk_fk IS 'Chave Estrangeira para o Id do Campeonato que a partida é disputada';
COMMENT ON	COLUMN tb_par_Partida.date_Data_pk IS 'Data que a partida é disputada';
COMMENT ON	COLUMN tb_par_Partida.str_Vitorioso_fk IS 'Chave Estrangeira para o CNPJ do Clube que venceu a partida (se houver - pode ser NULL)';
COMMENT ON	COLUMN tb_par_Partida.int_Gols_Mandante IS 'Gols marcados pelo Clube Mandante';
COMMENT ON	COLUMN tb_par_Partida.int_Gols_Visitante IS 'Gols marcados pelo Clube Visitante';

/* Criação dos ALIAS */
CREATE VIEW jgd AS SELECT * FROM tb_jgd_Jogador;
CREATE VIEW tec AS SELECT * FROM tb_tec_Técnico;
CREATE VIEW clu AS SELECT * FROM tb_clu_Clube;
CREATE VIEW cam AS SELECT * FROM tb_cam_Campeonato;
CREATE VIEW dis AS SELECT * FROM tb_dis_Disputa;
CREATE VIEW est AS SELECT * FROM tb_est_Estádio;
CREATE VIEW jga AS SELECT * FROM tb_jga_Joga;
CREATE VIEW par AS SELECT * FROM tb_par_Partida;

/* Criação Índice */
CREATE INDEX idx_Nome_cam ON tb_cam_Campeonato (str_Nome_cam);
CREATE INDEX idx_Nome_clu ON tb_clu_Clube (str_Nome_clu);


-- /* Função Valida CPF */

CREATE OR REPLACE FUNCTION cpf_validar(par_cpf varchar(11)) RETURNS integer AS $$
-- Retorna 1 para CPF correto.
DECLARE
vet_cpf integer [11]; --Recebe o CPF DIGITADO
dv integer; -- Primeiro número do DV (Dígito Verificador)
dv1 integer; -- Segundo número do DV (Dígito Verificador)
soma integer; -- Soma utilizada para o cálculo do DV
rest integer; -- Resto da divisão
BEGIN
IF char_length(par_cpf) = 11 THEN
ELSE
RAISE NOTICE 'Formato inválido: %',$1;
RETURN 0;
END IF;
-- Atribuição dos valores do Vetor
vet_cpf[0] := cast(substring (par_cpf FROM 1 FOR 1) as integer);
vet_cpf[1] := cast(substring (par_cpf FROM 2 FOR 1) as integer);
vet_cpf[2] := cast(substring (par_cpf FROM 3 FOR 1) as integer);
vet_cpf[3] := cast(substring (par_cpf FROM 4 FOR 1) as integer);
vet_cpf[4] := cast(substring (par_cpf FROM 5 FOR 1) as integer);
vet_cpf[5] := cast(substring (par_cpf FROM 6 FOR 1) as integer);
vet_cpf[6] := cast(substring (par_cpf FROM 7 FOR 1) as integer);
vet_cpf[7] := cast(substring (par_cpf FROM 8 FOR 1) as integer);
vet_cpf[8] := cast(substring (par_cpf FROM 9 FOR 1) as integer);
vet_cpf[9] := cast(substring (par_cpf FROM 10 FOR 1) as integer);
vet_cpf[10] := cast(substring (par_cpf FROM 11 FOR 1) as integer);
-- CÁLCULO DO PRIMEIRO NÚMERO DO DV
-- Soma dos nove primeiros multiplicados por 10, 9, 8 e assim por diante...
soma:=(vet_cpf[0]*10)+(vet_cpf[1]*9)+(vet_cpf[2]*8)+(vet_cpf[3]*7)+(vet_cpf[4]*6)+(vet_cpf[5]*5)+(vet_cpf[6]*4)+(vet_cpf[7]*3)+(vet_cpf[8]*2);
rest:=soma % 11;
if (rest = 0) or (rest = 1) THEN
dv:=0;
ELSE dv:=(11-rest); END IF;
-- CÁLCULO DO SEGUNDO NÚMERO DO DV 
-- Soma dos nove primeiros multiplicados por 11, 10, 9 e assim por diante...
soma:=(vet_cpf[0]*11)+(vet_cpf[1]*10)+(vet_cpf[2]*9)+(vet_cpf[3]*8)+(vet_cpf[4]*7)+(vet_cpf[5]*6)+(vet_cpf[6]*5)+(vet_cpf[7]*4)+(vet_cpf[8]*3)+(dv*2);
rest:=soma % 11;
if (rest = 0) or (rest = 1) THEN
dv1:=0;
ELSE dv1:=(11-rest); END IF;
IF (dv = vet_cpf[9]) and (dv1 = vet_cpf[10]) THEN
RETURN 1;
ELSE
RAISE NOTICE 'DV do CPF Inválido: %',$1;
RETURN 0; 
END IF;
END;
$$ LANGUAGE PLPGSQL;

/* Função auxiliar de verificação do CPF */

CREATE OR REPLACE FUNCTION validar_jgd()
	RETURNS trigger AS
		$BODY$
			DECLARE
				CPF VARCHAR(11);
				resultado integer;
			BEGIN
				SELECT NEW.str_CPF_jgd INTO CPF;
				SELECT cpf_validar(CPF)	INTO resultado;		
				IF resultado = 0 AND (CPF IS NOT NULL) THEN
					RAISE EXCEPTION 'CPF Inválido do jogador | resultado = (%)', resultado;
				END IF;
				RETURN NEW;
			END;
		$BODY$
	LANGUAGE plpgsql;
	
CREATE TRIGGER trg_valida_cpf
	BEFORE INSERT OR UPDATE
		ON tb_jgd_Jogador
			FOR EACH ROW
				EXECUTE PROCEDURE validar_jgd();

CREATE OR REPLACE FUNCTION validar_tec()
	RETURNS trigger AS
		$BODY$
			DECLARE
				CPF VARCHAR(11);
				resultado integer;
			BEGIN
				SELECT NEW.str_CPF_pk INTO CPF;
				SELECT cpf_validar(CPF)	INTO resultado;		
				IF resultado = 0 THEN
					RAISE EXCEPTION 'CPF Inválido do técnico | resultado = (%)', resultado;
				END IF;
				RETURN NEW;
			END;
		$BODY$
	LANGUAGE plpgsql;
	
CREATE TRIGGER trg_valida_cpf
	BEFORE INSERT OR UPDATE
		ON tb_tec_Técnico
			FOR EACH ROW
				EXECUTE PROCEDURE validar_tec();	

/* Função e trigger para time que não está no campeonato */ 

create or replace function participante_valido()
    returns trigger as $BODY$
      begin 
         if not exists (select *
              from tb_dis_Disputa as d
              where NEW.str_Mandante_pk_fk = d.str_CNPJ_pk_fk
              and NEW.int_Campeonato_pk_fk = d.int_Id_pk_fk)
               then raise exception 'mandante nao participa do campeonato' ;
         end if;
         if not exists (select *
              from tb_dis_Disputa as d
              where NEW.str_Visitante_pk_fk = d.str_CNPJ_pk_fk
              and NEW.int_Campeonato_pk_fk = d.int_Id_pk_fk)
             then raise exception 'visitante nao participa do campeonato' ; return null;
         end if;
         return new;
      end;
$BODY$ language plpgsql;

create trigger tg_participante_valido before insert or update 
       on tb_par_partida for each row
       execute procedure participante_valido();	

/* -------------------------------------------------------------------------------------------------------------------------------- */

INSERT INTO tb_jgd_Jogador VALUES (default, 'Neymar Junior', '40884441911', 'nj@mail.com', '11987006655', '10/01/1996'::date, 'atacante');
INSERT INTO tb_jgd_Jogador VALUES (default, 'Carlos Alberto Gomes', '33552201246', 'cag@mail.com', '2187776544', '10/19/1961'::date, 'atacante');
INSERT INTO tb_jgd_Jogador VALUES (default, 'Junior Bahiano', '77724275653', 'jbh@mail.com', '2187777655', '01/07/1999'::date, 'zagueiro');
-- /* Jogador e Técnico*/
INSERT INTO tb_jgd_Jogador VALUES (default, 'Romario Faria', '25583582278', 'romario@mail.com', '21976543322', '05/04/1975'::date, 'atacante');
-- /* Menor de idade - sem CPF */
INSERT INTO tb_jgd_Jogador VALUES (default, 'Matheus Alessandro',NULL , 'male@mail.com', '21987654432', '08/11/2005'::date, 'meia');
-- /* Jogador homônimo */
INSERT INTO tb_jgd_Jogador VALUES (default, 'Carlos Alberto Gomes', '15709204609', 'cag2@mail.com', '21987654433', '12/19/1970'::date, 'goleiro');

INSERT INTO tb_tec_Técnico VALUES ('33155384689', 'Mourinho', 'special1@hotmail.com', '24987677789', 'Manager');
INSERT INTO tb_tec_Técnico VALUES ('37420875847', 'Guardiola', 'tiktaka@hotmail.com', '22923451221', 'CEO');
INSERT INTO tb_tec_Técnico VALUES ('25583582278', 'Romario Faria', 'romario@mail.com', '21976543322', 'Auxiliar e Jogador'); /* Jogador e Técnico */
INSERT INTO tb_tec_Técnico VALUES ('53548776604', 'Renato Gaúcho', 'renatog@mail.com', '2199887711', 'Principal');

INSERT INTO tb_clu_Clube VALUES ('16883418000124', 'Fluminense', 'RJ', 1902, '37420875847');
INSERT INTO tb_clu_Clube VALUES ('39024578000113', 'Flamengo', 'RJ', 1912, '25583582278');
INSERT INTO tb_clu_Clube VALUES ('51943472000119', 'Bahia', 'BA', 1920, '33155384689');
INSERT INTO tb_clu_Clube VALUES ('62936049000108', 'Grêmio', 'RS', 1909, '53548776604');
INSERT INTO tb_clu_Clube VALUES ('34831518000199', 'Sport', 'PE', 1920, NULL); /* Clube sem Técnico */

INSERT INTO tb_cam_Campeonato VALUES (default, 'Brasileirão', 2017, '16883418000124', 10000000);
INSERT INTO tb_cam_Campeonato VALUES (default, 'Brasileirão', 2016, '16883418000124', 8000000);
INSERT INTO tb_cam_Campeonato VALUES (default, 'Brasileirão', 2015, '39024578000113', NULL); /* Premiação nula */
INSERT INTO tb_cam_Campeonato VALUES (default, 'Pernambucano', 2016, '34831518000199', 700000);
INSERT INTO tb_cam_Campeonato VALUES (default, 'Amistoso Bahia-Gremio', 2018, '62936049000108', 90000);

INSERT INTO tb_dis_Disputa VALUES ('16883418000124', 1, 88, 1);
INSERT INTO tb_dis_Disputa VALUES ('16883418000124', 2, 77, 1);
INSERT INTO tb_dis_Disputa VALUES ('39024578000113', 1, 50, 12);
INSERT INTO tb_dis_Disputa VALUES ('39024578000113', 2, 70, 10);
INSERT INTO tb_dis_Disputa VALUES ('39024578000113', 3, 40, 1);
INSERT INTO tb_dis_Disputa VALUES ('34831518000199', 4, 44, 1);
INSERT INTO tb_dis_Disputa VALUES ('34831518000199', 2, 15, 20); 
INSERT INTO tb_dis_Disputa VALUES ('51943472000119', 5, NULL, 2); /* Pontuação nula */
INSERT INTO tb_dis_Disputa VALUES ('51943472000119', 1, 67, 8);
INSERT INTO tb_dis_Disputa VALUES ('62936049000108', 5, NULL, 1); /* Pontuação nula */
INSERT INTO tb_dis_Disputa VALUES ('62936049000108', 1, 80, 2);

INSERT INTO tb_est_Estádio VALUES (default, 'Maracanã', 'RJ', 75000, '16883418000124');
INSERT INTO tb_est_Estádio VALUES (default, 'Ilha do Retiro', 'PE', 50000, '34831518000199');
INSERT INTO tb_est_Estádio VALUES (default, 'Edson Passos', 'RJ', 30000, NULL); /* Estádio sem dono */
INSERT INTO tb_est_Estádio VALUES (default, 'Estádio Ruim', 'SC', 10000, NULL);/* Estádio sem dono, vai ser deletado depois */

INSERT INTO tb_jga_Joga VALUES (1, '16883418000124', 'Principal');
INSERT INTO tb_jga_Joga VALUES (2, '16883418000124', 'Principal');
/* 3 ficou sem clube */
INSERT INTO tb_jga_Joga VALUES (4, '39024578000113', 'Principal');
INSERT INTO tb_jga_Joga VALUES (5, '39024578000113', 'Sub-20');
INSERT INTO tb_jga_Joga VALUES (6, '34831518000199', 'Reserva');

INSERT INTO tb_par_Partida VALUES ('16883418000124', '39024578000113', 1, 1, '07/10/2016'::date, '16883418000124', 3, 0);
INSERT INTO tb_par_Partida VALUES ('39024578000113', '16883418000124', 3, 1, '04/09/2017'::date, '16883418000124', 0, 1);
INSERT INTO tb_par_Partida VALUES ('62936049000108', '16883418000124', 3, 1, '04/09/2017'::date, '16883418000124', 0, 1);
INSERT INTO tb_par_Partida VALUES ('51943472000119', '16883418000124', 1, 1, '04/09/2017'::date, '16883418000124', 1, 2);
INSERT INTO tb_par_Partida VALUES ('34831518000199', '39024578000113', 2, 2, '07/11/2017'::date, NULL, 0, 0);




/* Erros */
-- INSERT INTO tb_jgd_Jogador (str_Nome_jgd) VALUES ('Andre Costa','19610230'); /* Numero de Argumentos Errado */
-- INSERT INTO tb_jgd_Jogador VALUES (default, 'Carlos Silva', '40884441911', 'cs@mail.com', '11907006655', '10/01/1995'::date, 'atacante'); /* CPF repetido */
-- INSERT INTO tb_jgd_Jogador VALUES (default, 'Carlos Silva', '40884441411', 'cs@mail.com', '11907006655', '10/01/1995'::date, 'atacante'); /* CPF Inválido */
-- INSERT INTO tb_jgd_Jogador VALUES (default, 'Carlos Silva', 'A084441411', 'cs@mail.com', '11907006655', '10/01/1995'::date, 'atacante'); /* CPF Inválido para jogador com caracter não numérico */
-- INSERT INTO tb_tec_Técnico VALUES ('742087584065', 'Guardiola', 'tiktaka@hotmail.com', 22923451221, 'CEO'); /* CPF inválido, mais de 11 números*/
-- INSERT INTO tb_tec_Técnico VALUES ('742087584065', 'Guardiola', 'tiktaka@hotmail.com', 229234a221, 'CEO'); /* CPF inválido, contém um caracter não numérico*/
-- INSERT INTO tb_tec_Técnico VALUES ('74208755406', 'Guardiola', 'tiktaka@hotmail.com', 2292347221, 'CEO'); /* CPF inválido técnico */
-- INSERT INTO tb_clu_Clube VALUES ('168834180005240', 'Fluminense', 'RJ', 1902, '37420875847'); /* CNPJ inválido, mais de 11 números */
-- INSERT INTO tb_clu_Clube VALUES ('57613883000122', 'Vasco', 'RJ', 1910, '45195844771'); /* CPF não representa nenhum Técnico */
-- INSERT INTO tb_clu_Clube VALUES ('57613883000122', 'Vasco', 'RJ', 1000, '37420875847'); /* Ano fundação inválido: <1500 */
-- INSERT INTO tb_clu_Clube VALUES ('57613883000122', 'Vasco', 'RJ', 3200, '37420875847'); /* Ano fundação inválido: >3000 */
-- INSERT INTO tb_cam_Campeonato VALUES (default, 'Brasileirão', 2016, NULL, 8000000); /* Argumentos NOT NULL zerados */
-- INSERT INTO tb_cam_Campeonato VALUES (default, 'Carioca', 2000, '16883418000124', 9999999999); /* Premiação inválida: >100000000 */
-- INSERT INTO tb_dis_Disputa VALUES ('16883418000124', 4, 1000, 1); /* Pontuação inválida: >100 */
-- INSERT INTO tb_dis_Disputa VALUES ('16883418000124', 4, 2, 70); /* Colocação inválida: >50 */
-- INSERT INTO tb_dis_Disputa VALUES ('16883418000124', 4, 88, 0); /* Colocação inválida: <1 */
-- INSERT INTO tb_est_Estádio VALUES (default, 'Gigantesco', 'DF', 150000, NULL); /* Capacidade inválida: >100000 */
-- INSERT INTO tb_par_Partida VALUES ('16883418000124', '39024578000113', 3, 1, '02/10/2017'::date, '16883418000124', 22, 0); /* Gols Mandante inválido: >20 */
-- INSERT INTO tb_par_Partida VALUES ('16883418000124', '39024578000113', 3, 1, '02/10/2017'::date, '16883418000124', 3, 30); /* Gols Visitante inválido: >20 */
-- INSERT INTO tb_par_Partida VALUES ('34831518000199', '39024578000113', 2, 2, '07/08/2017'::date, '34831518000199', 0, 0); /* Empate não pode ter vencedor */
-- INSERT INTO tb_jgd_Jogador VALUES (default, 'Manuel Lanzini', '21687331049', 'ML@mail.com', '11987654325', '1961/02/30'::date, 'atacante'); /* Data Inválida */
-- INSERT INTO tb_par_Partida VALUES ('34831518000199', '39024578000113', 2, 3, '07/07/2017'::date, '34831518000199', 1, 0); /* Sport mandante não está nesse campeonato */
-- INSERT INTO tb_par_Partida VALUES ('39024578000113', '34831518000199', 2, 3, '07/07/2017'::date, '34831518000199', 1, 0); /* Sport visitante não está nesse campeonato */

-- INSERT INTO tb_par_Partida VALUES ('34831518000199', '39024578000113', 2, 2, '07/15/2017'::date, '34831518000199', 0, 1); /* Vencedor não fez mais gols*/




/* UPDATE e DELETE*/
-- UPDATE tb_jgd_Jogador SET str_Posição = 'meia ofensivo' WHERE num_Registro_pk = 3;
-- UPDATE tb_cam_Campeonato SET int_Premiação = int_Premiação * 1.1 WHERE (int_Premiação > 100000);
-- UPDATE tb_jga_Joga SET str_Elenco = 'Reserva' WHERE int_Registro_pk_fk = 4;

-- DELETE FROM tb_est_Estádio WHERE str_Nome_est = 'Estádio Ruim';



 /* TRUNCATE TABELAS
TRUNCATE tb_jgd_Jogador;
TRUNCATE tb_tec_Técnico;
TRUNCATE tb_clu_Clube;
TRUNCATE tb_cam_Campeonato;
TRUNCATE tb_dis_Disputa;
TRUNCATE tb_est_Estádio;
TRUNCATE tb_jga_Joga;
TRUNCATE tb_par_Partida;
*/
