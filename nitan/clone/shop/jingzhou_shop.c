inherit SHOP;

void create()
{
        set("short", "五華樓");
        set("long", @LONG
五華樓位於荊州城北，來往於此的多是商富大賈。樓內裝
潢得非常典雅精緻，堪稱荊州城內一絕。不過此時店裏的貨櫃
上卻空無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
五華樓位於荊州城北，來往於此的多是商富大賈。樓內裝
潢得非常典雅精緻，堪稱荊州城內一絕。店裏的夥計正招呼着
前來購物的客人，忙得滿頭大汗。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/jingzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}