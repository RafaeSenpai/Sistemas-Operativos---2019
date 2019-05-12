int runAggregation(){
	int fdLog = open("LogFile",O_CREAT | O_RDWR,0777);
	int fdAgg = open(nameFileAggregation(),O_CREAT | O_RDWR,0777);
	int fdSales = open(SaleFile, O_RDONLY,0777);
	int nLastSaleAgg = -1;
	float qtV,valV;
	int codArt;

	if(fdLog>-1){
		read(fdLog,&nLastSaleAgg,sizeof(int));
		if(fdSales>-1){
			Venda sale = malloc(sizeof(struct Vendas));
			if(sale){
				if(fdAgg>-1){
					nLastSaleAgg++;
					lseek(fdSales,nLastSaleAgg*sizeof(struct Vendas),SEEK_SET);

					while(read(fdSales,sale,sizeof(struct Vendas))>0){
						codArt = sale->idArt;
						qtV = sale->quant;
						valV = sale->vTotal;
						lseek(fdAgg, codArt*sizeof(struct Vendas),SEEK_SET);

						if((read(fdAgg,sale,sizeof(struct Vendas)))==0){
							write(fdAgg,sale, sizeof(struct Vendas));
							lseek(fdLog,(-1)*sizeof(int),SEEK_END);//<<<<----- NÃO SEI SE É CORRETO FAZE-LO!
							
							write(fdLog,nLastSaleAgg,sizeof(int));
							nLastSaleAgg++;
						}else{
							sale->quant += qtV;
							sale->vTotal += valV;
							lseek(fdAgg,(codArt-1)*sizeof(struct Vendas), SEEK_SET);//<<<<----- NÃO SEI SE É CORRETO FAZE-LO!

							write(fdAgg,sale,sizeof(struct Vendas));
							lseek(fdLog,(-1)*sizeof(int),SEEK_END);
							write(fdLog,nLastSaleAgg,sizeof(int));
							nLastSaleAgg++;
						}
						lseek(fdSales,nLastSaleAgg*sizeof(struct Vendas),SEEK_SET);
					}
					close(fdAgg);//<<---Não pode ser feito snão dava é devolvido pela função!
					free(sale);
					close(fdSales);
					close(fdLog);
					return fdAgg;

				}else{
					free(sale);
					close(fdSales);
					close(fdLog);	
				}

			}else{
				close(fdSales);
				close(fdLog);
			}
		}else{
			close(fdLog);
		}
	}
}