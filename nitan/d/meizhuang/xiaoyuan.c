inherit ROOM;

void create()
{
        set("short", "琴心小院");
        set("long", @LONG
穿過月洞門，便是一座看起來非常普通的小小的院落，兩旁修竹
姍姍，花徑鵝卵石上生滿青苔，顯得平素少有人行。花徑通到三間石
屋之前。屋前屋後七八株蒼鬆夭矯高挺，遮得四下裡陰沉沉的。院子
裡沒有什麼擺設，只有幾堆幹木柴(wood)放在角落裡，其中有一捆特
別引人注目。 
LONG );
        set("exits", ([
                "south" : __DIR__"yuedong",
                "enter" : __DIR__"xiaowu",
        ]));

        set("item_desc",([
                "wood" : "一大堆幹柴，其中有一捆的顏色比較特別。\n",
        ]));
        set("objects", ([
                __DIR__"npc/shi" : 1,
        ]));

        set("outdoors", "meizhuang");

        setup();
}

void init()
{
        add_action("do_pull", "pull");
        add_action("do_unlock", "unlock");
        if (present("ding jian", environment(this_player())))
                delete("exits/east");
}
int do_unlock(string arg)
{
        object ob;
        if (query("exits/east"))
                return notify_fail("這扇門已經是打開的。\n");
        if (!arg || (arg != "men" && arg != "east"))
                return notify_fail("你要打開什麼？\n");
        if (!(ob = present("tong yaoshi", this_player())))
                return notify_fail("你不會撬鎖。\n");
        set("exits/east", "/d/meizhuang/mishi2");
        message_vision("$N把紅玉鑰匙放進門的凹陷處, 東邊的一扇門無聲的打開了。\n", this_player());
        destruct(ob);
        return 1;
}
int do_pull(string arg)
{
        object me , ob;
        me = this_player();
        if (arg == "wood" && !present("sea-wood", me) && query("weapon_count") >= 1)
        {
                addn("weapon_count", -1);
                ob=new("/d/meizhuang/obj/sea-wood");
                ob->move("/d/meizhuang/xiaoyuan");
                message_vision("$N在木柴堆裡撥弄著, 一根劍形的木棒掉了出來.\n", me);
                return 1;
        }
        else {
                message_vision("$N找了半天,也沒有發現什麼特別的東西.\n", me);
                return 1;
             }
}
int valid_leave(object me, string dir)
{
        object shi;

        if (dir != "enter" ||
            ! objectp(shi = present("shi lingwei", this_object())))
                return ::valid_leave(me, dir);

        return shi->permit_pass(me, dir);
}