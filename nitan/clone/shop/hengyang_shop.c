inherit SHOP;

void create()
{
        set("short", "祝融居");
        set("long", @LONG
這裏是衡陽城內的一家店鋪，衡陽城雖小，南嶽衡山卻尤
為著名。店鋪由衡山五峯之一的祝融峯而得名。從紅木雕窗放
眼望去，整個衡陽古城熙熙攘攘的街道盡收眼底。
LONG);
        set("open_long", @LONG
這裏是衡陽城內的一家店鋪，衡陽城雖小，南嶽衡山卻尤
為著名。店鋪由衡山五峯之一的祝融峯而得名。從紅木雕窗放
眼望去，整個衡陽古城熙熙攘攘的街道盡收眼底。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/henshan/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}