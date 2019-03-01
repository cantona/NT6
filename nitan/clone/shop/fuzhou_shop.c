inherit SHOP;

void create()
{
        set("short", "騰龍齋");
        set("long", @LONG
騰龍齋是福州城內有名的店舖，店堂正中掛著的一塊匾額
上寫著「騰蛟起風」四個大字，令人肅然起敬。不過店裡的貨
櫃上卻空無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
騰龍齋是福州城內有名的店舖，店堂正中掛著的一塊匾額
上寫著「騰蛟起風」四個大字，令人肅然起敬。整個舖面寬敞
明亮，櫃上擺滿了各式各樣、琳琅滿目的貨物。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/fuzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}