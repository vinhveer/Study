#include <iostream>
#include <windows.h>
using namespace std;

#define MAX 100
#define y 18

int n;
int Vitri[4];
unsigned char Hinhdia[MAX][MAX];
unsigned char Xoa[MAX];
int Docao[4];
int DiaTrongCot[4][MAX];

// gia lap ham gotoxy trong Windows
void gotoxy(int xx, int yy)
{
    COORD pos = {xx, yy};
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, pos);
}

void VevaKhoitao()
{
    int i, j;

    Vitri[1] = 4;  // toa do x cua cot 1
    Vitri[2] = 30; // toa do x cua cot 2
    Vitri[3] = 56; // toa do x cua cot 3

    Docao[1] = n; // cot 1 dang co n dia
    Docao[2] = 0; // cot 2 chua co dia
    Docao[3] = 0; // cot 3 chua co dia

    // Xoa la mot chuoi khoang trang gom 2*n+3 ky tu, de xoa cac dia trong qua trinh di chuyen
    for (i = 0; i < 2 * n + 3; i++)
        Xoa[i] = ' ';
    Xoa[i] = '\0';

    // Ve be do
    for (i = 1; i <= 3; i++)
    {
        gotoxy(Vitri[i], y);
        for (j = 1; j <= 2 * n + 3; j++)
            cout << "�";
    }

    // Khoi tao cac hinh dia
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j < n - i + 1; j++)
            Hinhdia[i][j] = ' ';
        for (j = n - i + 1; j < n - i + 1 + 2 * i + 1; j++)
            Hinhdia[i][j] = '�';
        Hinhdia[i][j] = ' ';
        Hinhdia[i][j + 1] = '\0';
    }

    // Ve cac dia ra cot 1
    for (i = 1; i <= n; i++)
    {
        gotoxy(Vitri[1], y - (n - i) - 1);
        cout << Hinhdia[i];
        DiaTrongCot[1][n - i + 1] = i;
    }
}

void Chuyen1dia(int Cotdi, int Cottoi)
{
    int i;
    unsigned char *dia;

    // lay dia tren cung o cot di
    dia = &Hinhdia[DiaTrongCot[Cotdi][Docao[Cotdi]]][0];

    // nang dia o cot di len
    for (i = Docao[Cotdi]; i < n + 1; i++)
    {
        gotoxy(Vitri[Cotdi], y - i);
        cout << Xoa;
        gotoxy(Vitri[Cotdi], y - i - 1);
        cout << dia;
        gotoxy(1, 1);
        Sleep(2000);
    }

    if (Cotdi < Cottoi) // chuyen dia sang phai
        for (i = Vitri[Cotdi]; i <= Vitri[Cottoi]; i++)
        {
            gotoxy(i, y - n - 1);
            cout << dia;
            gotoxy(1, 1);
            Sleep(25);
        }
    else // chuyen dia sang trai
        for (i = Vitri[Cotdi]; i >= Vitri[Cottoi]; i--)
        {
            gotoxy(i, y - n - 1);
            cout << dia;
            gotoxy(1, 1);
            Sleep(25);
        }

    // Ha dia xuong o cot toi
    for (i = n + 1; i > Docao[Cottoi] + 1; i--)
    {
        gotoxy(Vitri[Cottoi], y - i);
        cout << Xoa;
        gotoxy(Vitri[Cottoi], y - i + 1);
        cout << dia;
        gotoxy(1, 1);
        Sleep(50);
    }

    // Cap nhat lai cac dia o cot di va cot den
    Docao[Cottoi] += 1;
    DiaTrongCot[Cottoi][Docao[Cottoi]] = DiaTrongCot[Cotdi][Docao[Cotdi]];
    Docao[Cotdi] -= 1;
}

void HaNoi(int n, int a, int b, int c)
{
    if (n == 1)
        Chuyen1dia(a, b);
    else
    {
        HaNoi(n - 1, a, c, b);
        Chuyen1dia(a, b);
        HaNoi(n - 1, c, b, a);
    }
}

int main()
{
    do
    {
        cout << "Nhap vao so dia (1<=n<=6): ";
        cin >> n;
    } while (n < 1 || n > 6);
    VevaKhoitao();
    HaNoi(n, 1, 2, 3);

    system("pause");
    return 0;
}
