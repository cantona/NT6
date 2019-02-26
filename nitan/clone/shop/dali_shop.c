inherit SHOP;

void create()
{
        set("short", "翡翠園");
        set("long", @LONG
這裏是大理城內有名的店鋪翡翠園，大理地處天南，民眾
富饒。店鋪內裝飾得非常豪華，不過貨櫃上卻空無一物。夥計
在一旁打着盹，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
這裏是大理城內有名的店鋪翡翠園，店堂里人來人往，川
流不息。大理地處天南，出售的物品也是別具一格。鋪面寬敞
明亮，櫃上擺滿了各式各樣、琳琅滿目的貨物。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/dali/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}