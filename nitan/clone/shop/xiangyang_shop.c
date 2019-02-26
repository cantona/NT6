inherit SHOP;

void create()
{
        set("short", "聚義堂");
        set("long", @LONG
聚義堂坐落於襄陽城北街，雖然襄陽連年戰火不斷，但店
鋪內仍是佈置得井井有條。堂中掛着一個大大的義字，令人肅
然起敬。貨櫃上卻空無一物，想必是暫時停業了。
LONG);
        set("open_long", @LONG
聚義堂坐落於襄陽城北街，雖然襄陽連年戰火不斷，但店
鋪內仍是佈置得井井有條。堂中掛着一個大大的義字，令人肅
然起敬。店鋪裏的夥計正招呼着客人。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/xiangyang/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}