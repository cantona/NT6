// qianting.c 盤龍居前庭

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        object ob;

        set("short", "前庭");             /* EXAMPLE */
//**    set("short", "ROOM_NAME前庭");
        set("long", @LONG
這裡似乎非常安靜，倒是時不時聽見鳥兒唧唧喳喳的叫。院中不少樹
木已然有遮天之勢，肅穆非常。
LONG );

        set("default_long", "這裡似乎非常安靜，聽不到什麼聲響，到是時不" /* EXAMPLE */
                            "時聽見鳥兒唧唧喳喳的叫。院中不少樹木已然有" /* EXAMPLE */
                            "遮天之勢，肅穆非常。");                     /* EXAMPLE */
                                                                         /* EXAMPLE */

        set("exits", ([
                "south"  : __DIR__"dayuan",
                "east"   : __DIR__"zuowei",
                "west"   : __DIR__"youwei",
        ]));

//**    set("objects", ([
//**            "/adm/npc/laopu" : 1,
//**    ]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        set("gate", "close");
        setup();

//**    ob = present("saodi laopu", this_object());
//**    ob->set("coagents", ({
//**            ([ "startroom" : __DIR__"zuowei",
//**               "id"        : "shou wei 2" ]),
//**            ([ "startroom" : __DIR__"zuowei",
//**               "id"        : "shou wei 1" ]),
//**            ([ "startroom" : __DIR__"youwei",
//**               "id"        : "shou wei 2" ]),
//**            ([ "startroom" : __DIR__"youwei",
//**               "id"        : "shou wei 1" ]),
//**    }));

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
        add_action("do_push", "push");
        add_action("do_close", "close");
}

int do_push()
{
        object ob;
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("大門開著呢，你還推什麼？\n");

        me = this_player();
        ob = present("saodi laopu", this_object());
        if (me && (! ob || ! living(ob) || ob->is_owner_permit(me)))
        {
                message_vision("$N用力一推大門，就聽見大門“吱呀呀”的開了。\n",
                               me);
        } else
        if (me && ! ob->is_owner(me))
        {
                message_vision("$N伸手攔住$n，客客氣氣道：“對不起，這位" +
                               RANK_D->query_respect(me) + "還是請回"
                               "吧！”\n", ob, me);
                return 1;
        } else
        if (ob && living(ob))
        {
                message_vision("$n連忙跑上前來，對$N道：“主人何必親"
                        "勞，我來吧！”\n$n走上前去，用力將大門“吱呀"
                        "呀”的推開了。\n", me, ob);
        } else
        {
                message("vision",  "大門“吱呀呀”的被人打開了。\n",
                        this_object());
        }

        room = get_object(__DIR__"zoudao");
        message("vision", "大門“吱呀呀”的被人推開了。\n", room);
        set("gate", "open");
        set("exits/north", __DIR__"zoudao");
        set("exits/south", __FILE__, room);
        set("gate", "open", room);
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object ob;
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("大門關著呢，你還再關一遍？\n");

        me = this_player();
        ob = present("saodi laopu", this_object());
        if (! n && me && (! ob || ! living(ob)))
        {
                message_vision("$N用力一拉大門，就聽見大門“吱呀呀”的關上了。\n",
                               me);
        } else
        if (! n && me && ! ob->is_owner(me))
        {
                message_vision("$N走上前去，用力合上大門。\n", me);
        } else
        if (! n && me && ob->is_owner(me))
        {
                message_vision("$n連忙跑上前來，對$N道：“主人何必"
                        "親勞，我來吧！”\n$n走上前去，用力合上大門。\n",
                        me, ob);
        } else
        if (ob && living(ob))
        {
                message("vision", ob->name() + "走上前去，用力合上大門。\n",
                        this_object());
        } else
        {
                message("vision", "大門“吱呀呀”的被人關上了。\n",
                        this_object());
        }

        room = get_object(__DIR__"zoudao");
        message("vision", "大門“吱呀呀”的被人關上了。\n", room);
        set("gate", "close");
        delete("exits/north");
        delete("exits/south", room);
        set("gate", "close", room);
        return 1;
}

string long()
{
        string msg;
        msg = "    ";
        if (present("lao jiaren"))
                msg += "一老家人慢慢的揮舞著掃把，打掃著落葉。";

        if (query("gate") != "open")
                msg += "向北望去，有一扇大門緊緊的關閉著。";
        else
                msg += "大門暢開，遠遠望去，隱然可見迎客廳。";

        return query("long") + sort_string(msg, 60, 0);
}

int valid_leave(object me, string dir)
{
        object ob;

        ob = present("saodi laopu", this_object());
        if (dir != "north" || ! objectp(ob) || ! living(ob))
                return ::valid_leave(me, dir);

        if (ob->is_owner(me))
        {
                message_vision("$N彎腰對$n道：“請進！”\n", ob, me);
                return ::valid_leave(me, dir);
        }

        if (ob->is_owner_permit(me))
        {
                message_vision("$N對$n道：“即然是主人的朋友，但進無妨。”\n",
                               ob, me);
                return ::valid_leave(me, dir);
        }

        message_vision("$N伸手攔住$n，道：“非請莫入！”\n", ob, me);
        return 0;
}