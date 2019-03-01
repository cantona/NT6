inherit SHOP;

void create()
{
        set("short", "萬景莊");
        set("long", @LONG
這裡是開封城內有名的店舖萬景莊，開封為百年古都，民
眾富饒。店舖內裝飾得非常豪華，不過櫃上卻空無一物。伙計
在一旁打著盹，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
這裡是開封城內有名的店舖萬景莊，店堂裡人來人往，川
流不息。開封為百年古都，出售的物品也是別具一格。舖面寬
敞明亮，櫃上擺滿了各式各樣、琳琅滿目的貨物。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/kaifeng/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}