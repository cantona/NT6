// Room: /d/kunlun/songshu.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "鬆樹");
        set("long", @LONG
這是一株長于峭壁上的鬆樹。向上而望，不能看見懸之上之物，剛
才從上而跳下之時，回想起來你自不禁心悸，額頭冷汗涔涔而下，一看
四下形勢，向上而攀援是絕不可能，腳下深不見底。便算到了底下，十
之八九也是沒有出路，唯有沿著山壁斜坡，慢慢的爬行出去。
LONG        );
        set("exits",([
        ]));
        set("no_clean_up", 0);
        set("coor/x", -100030);
        set("coor/y", 20010);
        set("coor/z", 40);
        set("outdoors", "hongmei");
        setup();
}
void init()
{
        add_action("do_pa","pa");
}
int do_pa(string arg)
{
        object me;
        me=this_player();
        if (!(arg||arg=="east"||arg=="west")) return 0;
        if (arg=="east"){
                message("vision",me->name()+"向著太陽升起的地方爬去。\n",environment(me),me);
                write("你向東面的雪山斜坡爬去。\n");
                me->move(__DIR__"xsxiepo1");
                message("vision",me->name()+"從鬆樹爬了過來。\n",environment(me),me);
                return 1;
        }
        if (arg=="west")
        {
                message("vision",me->name()+"向西邊爬去。\n",environment(me),me);
                write("你向西面的懸崖爬去。\n");
                me->move(__DIR__"xuanya1");
                message("vision",me->name()+"從鬆樹爬了過來。\n",environment(me),me);
                return 1;
        }
        return 1;
}