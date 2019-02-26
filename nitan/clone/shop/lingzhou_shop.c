// lingzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
        set("short", "同福居");
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/lingzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}

void init()
{
        if (query("shop_type") == 0)
                set("long", @LONG
這裏便是靈州城裏最有名的同福居，塞上江南，真是名不虛傳，店
裏陳設清新可人，儼然江南名店一般。不過店裏的貨櫃上卻空無一物，
看樣子已經很久沒人來打理了。
LONG);
        else
                set("long", @LONG
這裏便是靈州城裏最有名的同福居，塞上江南，真是名不虛傳，店
裏陳設清新可人，儼然江南名店一般。鋪面寬敞明亮，櫃上擺滿了各式
各樣、琳琅滿目的貨物。
LONG);
        return;
}