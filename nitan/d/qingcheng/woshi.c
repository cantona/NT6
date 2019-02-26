// woshi.c

inherit ROOM;
int do_open(string arg);

void create()
{
        set("short", "卧室");
        set("long", @LONG
這裏是餘滄海的寢室。餘滄海雖然是道家弟子，可也不禁婚約。因
此他娶了正配，還一氣陪進來好幾個小妾。卧室中擺着一張楠木花雕大
牀，一具紅松大衣櫃，櫃頂擱着幾隻牛皮藤箱子，牆角立着一張有點陳
舊的梳粧枱 (tai)，靠窗(window)處是一張花梨木書桌。
LONG
        );
        set("key", 1);
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"garden",
        ]));
        set("item_desc", ([
                "window" : "窗外就是天下幽的青城了。\n",
                "tai"    : "一張紅漆鑲玉邊的半開的梳粧枱。\n",
        ]));
        set("objects", ([
                __DIR__"npc/yuwife" : 1,
        ])  ) ;

        set("coor/x", -8070);
        set("coor/y", -820);
        set("coor/z", 90);
        setup();
}
void init()
{
        add_action("do_open", "open");
        add_action("do_open", "kai");
}

int do_open(string arg)
{
        object key, me=this_player();

        if( !arg || arg!="tai" ) return 0;

        if( arg=="tai" )
        {
                if( (query("family/master_id", me) != "yucanghai") && 
                        objectp(present("yu wife", environment(me))))
                {
                        return notify_fail(
"餘小星喝道：這位" + RANK_D->query_respect(me) + "，你不能隨便翻人家東西。\n");
                        return 1;
                }
                if (query("key"))
                {
                        message_vision(
"$N輕輕的打開梳粧枱抽屜，發現裏面有一支鐵鑰匙。\n", me);
                        key = new(__DIR__"obj/key2");
                        key->move(__FILE__);
                        set("key", 0);
                        return 1;
                }
                message_vision(
"$N輕輕的拉開抽屜，可是裏面啥都沒有...。\n", me);
                return 1;
        }
        return 0;
}