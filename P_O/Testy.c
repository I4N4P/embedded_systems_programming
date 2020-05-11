#include "lancuchyznakowe1.h"
#include "lancuchyznakowe2.h"
#include "dekodowanie.h"
#include <stdio.h>
#include <string.h>


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//pozmieniajcie zmienne i komentarze troche
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void TestOf_CopyString(void) {

	printf("CopyString\n\n ");

	printf("Test 1 - ");
	//oba tej samej dlugosci
	char cAfterCopy1[]="fghij";
	CopyString("uwaga", cAfterCopy1);
	if (strcmp("uwaga", cAfterCopy1)==0){
		printf("OK\n\n ");
	}
	else{
		printf("Error\n\n ");	
	}
	
	printf("Test 2 - ");
	//pierwszy wyraz pusty
	char cAfterCopy3[]="fghij";
	CopyString("", cAfterCopy3);
	if (strcmp("", cAfterCopy3)==0){
		printf("OK\n\n ");
	}
	else{
			printf("Error\n\n ");
	}
}
printf("Test 3 - ");
	//pierwszy wyraz krotszy
	char cAfterCopy2[]="fghij";
	CopyString("twoj", cAfterCopy2);
	if (strcmp("twoj", cAfterCopy2)==0){
		printf("OK\n\n "); 
	}
	else{
		printf("Error\n\n ");	
	}
//----------------------------------------------------------
void TestOf_eCompareString(void) {

	printf("eCompareString\n\n ");

	printf("Test 1 - ");
	//takie same, ta sama dlugosc
	if (eCompareString("uwaga", "uwaga")==EQUAL) printf("OK\n\n "); else printf("Error\n\n ");

	printf("Test 2 - ");
	//rozne, ta sama dlugosc
	if (eCompareString("uwaga", "ubran")==DIFFERENT) printf("OK\n\n "); else printf("Error\n\n ");

	printf("Test 3 - ");
	///pierwszy pusty
	if (eCompareString("", "ubran")==DIFFERENT) printf("OK\n\n "); else printf("Error\n\n ");

	printf("Test 4 - ");
	//drugi pusty
	if (eCompareString("uwaga", "")==DIFFERENT) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 5 - ");
	///oba puste
	if (eCompareString("", "")==EQUAL) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 6 - ");
	///drugi dluzszy
	if (eCompareString("uwaga", "nieobecny")==DIFFERENT) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_AppendString(void) {

	printf("AppendString\n\n ");

	printf("Test 1 - ");
	//dowolne
	char cAppendingTest1[]="ubran";
	AppendString("uwaga", cAppendingTest1);
	if (strcmp(cAppendingTest1, "ubranuwaga")==0) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//pierwszy pusty
	char cAppendingTest2[]="ubran";
	AppendString("", cAppendingTest2);
	if (strcmp(cAppendingTest2, "ubran")==0) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 3 - ");
	//drugi pusty
	char cAppendingTest3[]="";
	AppendString("uwaga", cAppendingTest3);
	if (strcmp(cAppendingTest3, "uwaga")==0) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_ReplaceCharactersInString(void) {

	printf("ReplaceCharactersInString\n\n ");

	printf("Test 1 - ");
	//rozne znaki
	char cOryginal1[]="Tekst do zamiany znaku";
	ReplaceCharactersInString(cOryginal1, 'a', 'A');
	if (strcmp(cOryginal1, "Tekst do zAmiAny znAku")==0) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//spacja na NULL
	char cOryginal2[]="Tekst do zamiany znaku";
	ReplaceCharactersInString(cOryginal2, ' ', '\0');
	if (strcmp(cOryginal2, "Tekst\0do\0zamiany\0znaku")==0) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_UIntToHexStr(void) {
	
	printf("UIntToHexStr\n\n ");

	printf("Test 1 - ");
	//krance przedzialow, 0,9,10,15
	char cAfterConverion[6];
	UIntToHexStr(0x09AF, cAfterConverion);
	if (strcmp(cAfterConverion, "0x09AF")==0) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//zera po x w stringu
	UIntToHexStr(0x34, cAfterConverion);
	if (strcmp(cAfterConverion, "0x0034")==0) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_eHexStringToUInt() {
	
	enum Result iReturnResult;
	unsigned int uiReturnValue;
		
	printf("eHexStringToUInt\n\n ");
	
	printf("Test 1 - ");
	//krance przedzialow
	iReturnResult = eHexStringToUInt("0x09AF", &uiReturnValue);
	if (iReturnResult==OK) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//za krotki
	iReturnResult = eHexStringToUInt("0x", &uiReturnValue);
	if (iReturnResult==ERROR) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 3 - ");
	//za dlugi
	iReturnResult = eHexStringToUInt("0xFFDC2", &uiReturnValue);
	if (iReturnResult==ERROR) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 4 - ");
	//poczatek rozny od 0x
	iReturnResult = eHexStringToUInt("klhfcsd", &uiReturnValue);
	if (iReturnResult==ERROR) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 5 - ");
	//mniej znakow
	iReturnResult = eHexStringToUInt("0x034", &uiReturnValue);
	if (iReturnResult==OK) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_AppendUIntToString() {	
	
	printf("AppendUIntToString\n\n ");
	
	printf("Test 1 - ");
	//niepusty string, dopisywanie od NULLa
	char cOryginal1[]="Jakis tekst";
	AppendUIntToString(0x1234,cOryginal1);
	if (strcmp(cOryginal1,"Jakis tekst0x1234")==0) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//pusty string
	char cOryginal2[]="";
	AppendUIntToString(0x1234,cOryginal2);
	if (strcmp(cOryginal2,"0x1234")==0) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_ucFindTokensInString() {
	
	unsigned char ucTokenNumber;
	
	printf("ucFindTokensInString\n\n ");
	
	printf("Test 1 - ");
	//max liczba tokenow
	ucTokenNumber=ucFindTokensInString("0x3343 ABDCDEFGH reset");
	if (ucTokenNumber==3) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//same delimitery
	ucTokenNumber=ucFindTokensInString("    ");
	if (ucTokenNumber==0) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 3 - ");
	//delimitery na poczatku stringu, mniej tokenow niz maks
	ucTokenNumber=ucFindTokensInString("   0x3343 ABDCDEFGH ");
	if (ucTokenNumber==2) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 4 - ");
	//kilka delimiterow pomiedzy tokenami
	ucTokenNumber=ucFindTokensInString("0x3343   ABDCDEFGH      reset");
	if (ucTokenNumber==3) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 5 - ");
	//za duzo tokenow, (zwraca 3 i ustawia wskazniki na pierwsze 3)
	char pcTestString[]="0x3343 ABDC DEFGH reset";
	ucTokenNumber=ucFindTokensInString(pcTestString);
	if ((ucTokenNumber==3) && (&pcTestString[0]==asToken[0].uValue.pcString)
			&& (&pcTestString[7]==asToken[1].uValue.pcString)
			&& (&pcTestString[12]==asToken[2].uValue.pcString)) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_eStringToKeyword() {
	
	enum KeywordCode eTokenCode;
	
	printf("eStringToKeyword\n\n ");
	
	printf("Test 1 - ");
	//slowo kluczowe
	if (eStringToKeyword("reset", &eTokenCode)==OK) printf("OK\n\n "); else printf("Error\n\n ");
	
	printf("Test 2 - ");
	//brak slowa kluczowego
	if (eStringToKeyword("jakis", &eTokenCode)==ERROR) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
void TestOf_DecodeTokens() {

	unsigned char ucTokenNumber;
	
	char pcSource1[]="0x3343 ABDCDEFGH reset";
	
	printf("DecodeTokens\n\n ");
	
	printf("Test 1 - ");
	//liczba i zapis jej, string i ustawienie wskaznika, keyword i zapis kodu
	ucTokenNumber=ucFindTokensInString(pcSource1);
	ReplaceCharactersInString(pcSource1,' ',NULL);
	DecodeTokens();		
	if ((asToken[0].eType==NUMBER) && (asToken[0].uValue.uiNumber==0x3343) &&
			(asToken[1].eType==STRING) && (&pcSource1[7]==asToken[1].uValue.pcString) &&
			(asToken[2].eType==KEYWORD) && (asToken[2].uValue.eKeyword==RST)) printf("OK\n\n\n"); else printf("Error\n\n\n");
} 
//----------------------------------------------------------
void TestOf_DecodeMsg() {
	
	char pcToDecode[]="0x3343 ABDCDEFGH reset";
	
	printf("DecodeMsg\n\n ");
	
	printf("Test 1 - ");
	//liczba, string, keyword
	DecodeMsg(pcToDecode);		
	if ((asToken[0].eType==NUMBER) && (asToken[0].uValue.uiNumber==0x3343) &&
			(asToken[1].eType==STRING) && (&pcToDecode[7]==asToken[1].uValue.pcString) &&
			(asToken[2].eType==KEYWORD) && (asToken[2].uValue.eKeyword==RST)) printf("OK\n\n\n"); else printf("Error\n\n\n");
}
//----------------------------------------------------------
int main(void) {
	
	printf("TESTY FUNKCJI - LANCUCHY ZNAKOWE - OPERACJE PROSTE\n\n\n");

	TestOf_CopyString();
	TestOf_eCompareString();
	TestOf_AppendString();
	TestOf_ReplaceCharactersInString();
	
	printf("TESTY FUNKCJI - LANCUCHY ZNAKOWE - KONWERSJE\n\n\n");
	
	TestOf_UIntToHexStr();
	TestOf_eHexStringToUInt();
	TestOf_AppendUIntToString();
	
	printf("TESTY FUNKCJI - DEKODOWANIE KOMUNIKATOW\n\n\n");
	
	TestOf_ucFindTokensInString();
	TestOf_eStringToKeyword();
	TestOf_DecodeTokens();
	TestOf_DecodeMsg();
}
