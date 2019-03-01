// Room: /d/taohua/boat.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

int do_turn(string);
int do_save();
int do_quit();
int do_goto();
int do_home();
int do_gg();
int do_tiaowang();
int ABS(int x);

void create()
{
        set("short", "船上");
        set("long", @LONG
小船已經來到了茫茫大海上。四周除了偶爾掠過頭頂的海鳥外，就
只剩下你所乘坐的這艘小船和正在聚精會神地搖著櫓的梢公了。海風陣
陣襲來，你不禁感到一絲涼意。
LONG
        );
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/shaogong":1,
        ]));
        set("no_fight",1);
        set("no_sleep_room",1);
        set("outdoors","taohua");
        set("coor/x", 5000);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
}

void init()
{
        object ob = this_player();

        if (!userp(ob)) return;
        if (query_temp("busy")) {
                if (!wizardp(ob)) {
                        message_vision("艄公對$N喝道：怎麼？想白坐嗎！\n",ob);
                        message_vision("艄公一槳將$N打落到海裡。\n",ob);
                        ob->unconcious();
                        ob->move("/d/jiaxing/haibin");
                        message("vision","忽然一個大潮湧了過來，將一個被水泡得半死的家伙沖到了岸邊。\n",environment(ob),ob);
                        return;
                }
                else {
                        message_vision("艄公無奈地對$N說道：當巫師就是好，船都可以白坐。\n",ob);
                        return;
                }
        }
        set_temp("busy", 1);
        add_action("do_turn","turn");
        add_action("do_turn","zhuan");
        add_action("do_save","save");
        add_action("do_quit","quit");
        add_action("do_goto", "goto");
        add_action("do_gg", "gg");
        add_action("do_home", "home");
        add_action("do_tiaowang","tiaowang");
        delete_temp("thd_dir", ob);
        if( query_temp("thd_target", ob) == "bay" )
        {
                set_temp("thd_locx",query("thd/x",  ob), ob);
                set_temp("thd_locy",query("thd/y",  ob), ob);
        }
        else { 
                set_temp("thd_target", "thd", ob);
                set_temp("thd_locx", 1, ob);
                set_temp("thd_locy", 1, ob);
        }
        
        call_out("time_limit1", 360, ob);
        call_out("weizhi", 3, ob);
}

int do_save()
{
        write("這裡不準存盤！\n");
        return 1;
}

int do_quit()
{
        write("這裡不準退出！\n");
        return 1;
}

int do_goto()
{
        if (wiz_level(this_player()) > 0)
                delete_temp("busy");
        return 0;
}

int do_home()
{
        if (wiz_level(this_player()) > 1)
                delete_temp("busy");
        return 0;
}

int do_gg()
{
        if (wiz_level(this_player()) > 2)
                delete_temp("busy");
        return 0;
}

void time_limit1(object ob)
{
        if (!present(ob, this_object()))
        {
                delete_temp("busy");
                return;
        }
        message_vision("艄公對$N說道：客官，要起風了，我們回去吧！\n", ob);
        call_out("time_limit2", 180, ob);
}

void time_limit2(object ob)
{
        if (!present(ob, this_object()))
        {
                delete_temp("busy");
                return;
        }
        message_vision("艄公對$N說道：客官，再劃下去咱們可都要死在海上了，你不要命我還要哪！\n", ob);
        write("艄公再也不理會你的命令，徑直劃回了岸邊。\n");
        delete_temp("thd_dir", ob);
        remove_call_out("weizhi");
        delete_temp("busy");
        if( query_temp("thd_target", ob) == "bay")ob->move(__DIR__"shore");
        else ob->move("/d/jiaxing/jiaxinggang");
}

int do_turn(string arg)
{
        string dir;
        object ob = this_player();

        switch(arg) {
                case "e": 
                case "east": 
                        dir = "東";
                        break;
                case "w": 
                case "west": 
                        dir = "西";
                        break;
                case "n": 
                case "north": 
                        dir = "北";
                        break;
                case "s": 
                case "south": 
                        dir = "南";
                        break;
                default:
                        return notify_fail("你要往哪個方向開？\n");
        }
        set_temp("thd_dir", arg[0..0], ob);
        message_vision("$N對艄公說：向" + dir + "開。\n", ob);
        message_vision("艄公對$N應道：好的，到了位置(weizhi)我自然會告訴您。您要想眺望(tiaowang)也隨便您。\n",ob);
        return 1;
}

int do_tiaowang()
{
        int viewdist = 10;
        object ob = this_player();

        if (present("wangyuan jing", ob)) viewdist = 10;
        if( (ABS(query_temp("thd_locx", ob)-query("thd/x", ob) )
        +ABS(query_temp("thd_locy", ob)-query("thd/y", ob)) <= viewdist )
         && query_temp("thd_target", ob) == "thd" )
        {
                message_vision("艄公指著遠處對$N說道：客官，那邊就是桃花島了，我這就劃過去。\n", ob);
                write("艄公一撐竹桿，將船慢慢地劃向了岸邊。\n");
                remove_call_out("time_limit1");
                remove_call_out("time_limit2");
           //ob->move(__DIR__"haitan");
                delete_temp("busy");
                return 1;
        }
        if( (ABS(query_temp("thd_locx", ob)-1 )
        +ABS(query_temp("thd_locy", ob)-1) <= viewdist )
         && query_temp("thd_target", ob) == "bay" )
        {
                message_vision("艄公指著遠處對$N說道：客官，那邊就是漁港了，我這就劃過去。\n", ob);
                write("艄公一撐竹桿，將船慢慢地劃向了岸邊。\n");
                remove_call_out("time_limit1");
                remove_call_out("time_limit2");
                ob->move("/d/jiaxing/jiaxinggang");
                delete_temp("busy");
                return 1;
        }
        return notify_fail("你極目遠眺，可是除了大海外卻什麼也看不到。\n");
}

void weizhi(object ob)
{
        int locx=query_temp("thd_locx", ob);
        int locy=query_temp("thd_locy", ob);
        string dir=query_temp("thd_dir", ob);

        if (!present(ob, this_object())) {
                delete_temp("busy");
                remove_call_out("time_limit1");
                remove_call_out("time_limit2");
                return;
        }
        if (!dir) {
                call_out("weizhi", 3, ob);
                if (!random(3))
                        message_vision("艄公不耐煩地對$N說：客官到底走不走啊？\n", ob);
                return;
        }
        switch (dir) {
                case "e": 
                        dir = "東";
                        if (locy > 0) locx++;
                        break;
                case "w": 
                        dir = "西";
                        if (locx == 1) message_vision("艄公對$N說：客官,要撞到岸邊了。\n", ob);
                        if (locx > 0 && locy > 0) locx--;
                        break;
                case "n": 
                        dir = "北";
                        if (locy == 1) message_vision("艄公對$N說：客官,要撞到岸邊了。\n", ob);
                        if (locy > 0 && locx > 0) locy--;
                        break;
                case "s": 
                        dir = "南";
                        if (locx > 0) locy++;
                        break;
        }
        if (locx < 1 || locy < 1) message_vision("小船停在了岸邊。換個方向開吧。\n", ob);
        else message_vision("小船正向著" + dir + "方前進。\n", ob);
        if( locx == query("thd/x", ob) && locy == query("thd/y", ob )
         && query_temp("thd_target", ob) == "thd" )
        {
                message_vision("艄公對$N說道：客官，桃花島到了，請下船吧。\n", ob);
                remove_call_out("time_limit1");
                remove_call_out("time_limit2");
                ob->move(__DIR__"shore");
                delete_temp("busy");
                return;
        }
        if( locx == 1 && locy == 1 && query_temp("thd_target", ob) == "bay" )
        {
                message_vision("艄公對$N說道：客官，漁港到了，請下船吧。\n", ob);
                remove_call_out("time_limit1");
                remove_call_out("time_limit2");
                ob->move("/d/jiaxing/jiaxinggang");
                delete_temp("busy");
                return;
        }

        set_temp("thd_locx", locx, ob);
        set_temp("thd_locy", locy, ob);
        call_out("weizhi", 3, ob);
}

int ABS(int x)
{
        if (x >= 0) return (x); else return -(x);
}
