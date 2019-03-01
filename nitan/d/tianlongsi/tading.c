inherit ROOM;

string look();
void create()
{
        set("short", "塔頂");
        set("long", @LONG
這是舍利塔塔頂，室中孤零零地放着一張供桌(zhuozi)。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
            "down" : __DIR__"ta1",
        ]));
        set("item_desc",([
            "zhuozi" : (:look():),
        ]));        
        set("no_clean_up", 0);
        setup();
}

string look()
{
        object me=this_player();
        set_temp("marks/ask_temp0", 1, me);
        return "那是原來供奉舍利子的地方，如今空空如也，看來江湖中傳言不虛。\n";
}