
#include <stdio.h>
#include <string.h>
#include "Strings1.h"
#include "String2.h"

/*void TestOf_CopyString(void) {

	printf("CopyString\n\n ");

	printf("Test 1 - ");
	//oba tej samej dlugosci
	char cAfterCopy1[]="fghij";
	char cAfterCopy2[]="uwaga";
	CopyString(cAfterCopy2, cAfterCopy1);
	if (strcmp("uwaga", cAfterCopy1)==0){
		printf("OK\n\n ");
	}
	else{
		printf("Error\n\n ");	
	}
	
	printf("Test 2 - ");
	//pierwszy wyraz pusty
	char cAfterCopy3[]="fghij";
	char cAfterCopy4[]="";
	CopyString(cAfterCopy4, cAfterCopy3);
	if (strcmp("", cAfterCopy3)==0){
		printf("OK\n\n ");
	}
	else{
			printf("Error\n\n ");
	}
}
printf("Test 3 - ");
	//pierwszy wyraz krotszy
	char cAfterCopy5[]="fghij";
	char cAfterCopy6[]="twoj";
	CopyString(cAfterCopy6, cAfterCopy2);
	if (strcmp("twoj", cAfterCopy2)==0){
		printf("OK\n\n "); 
	}
	else{
		printf("Error\n\n ");	
	}
*/
//----------------------------------------------------------
/*void TestOf_eCompareString(void) {

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
*/
char  Source[]  =  "Ala ma Kota";
char Destination[]="ALA MA KOTA";
	
int main(){
	
	while(1){

	
		CopyString(Source,Destination);

	}
}
