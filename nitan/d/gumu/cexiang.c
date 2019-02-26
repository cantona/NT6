// cexiang.c 側廂
// Java Oct.10 1998

inherit ROOM;
void back(object me);
void init();
int do_sleep(string arg);

void create()
{
        set("short", "側廂");
        set("long", @LONG
這裏是古墓中的側廂房。房間裏面黑呼呼的，什麼東西都沒有，只
有一條細繩(rope)，在室東的一根鐵釘上繫住，拉繩橫過室中，繩子的
另端系在西壁的一口釘上，繩索離地約莫一人來高。
LONG );

        set("exits", ([
                "west" : __DIR__"mudao14",
        ]));
        set("item_desc", ([
                "rope" : "一條細麻繩，看來是古墓弟子們睡眠之所。\n"
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3180);
        set("coor/y", -40);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_sleep", "sleep");
}

int do_sleep(string arg)
{
        object room, *ob, me=this_player();
        int i, j;

        if( !(room = find_object(__DIR__"rope")) )
                room = load_object(__DIR__"rope");
        if( !arg || arg != "rope" )
        {
                return notify_fail("你要睡在哪兒？\n");
        }
        if((int)me->query_skill("yunv-xinfa",1) < 10)
        {
                message_vision("$N的玉女心法不夠嫻熟，跳不上繩去。\n",me) ;
                return 1;
        }
        me->receive_damage("qi",random(30));
        ob = all_inventory(room);
        j = 0;
        for(i=0; i<sizeof(ob); i++)
                if( living(ob[i]) && ob[i] != me ) j++;
        if (j > 0)
        {
                message_vision("$N輕輕縱起，發現繩上有人，只好飛身下地。\n",me);
                return 1;
        }
        message_vision("$N輕輕縱起，橫卧繩上，以繩為牀，睡起覺來。\n", me);
        me->move(room) ;
        call_out("back", 6 , me);
        return 1 ;
}

void back( object me )
{
        int c_exp,c_skill;
        me->move(__DIR__"cexiang");
        message_vision("$N一覺醒來，飛身躍下繩來。\n",me);
        c_exp=query("combat_exp", me);
        c_skill=me->query_skill("dodge",1);
        if ((random(10)>3) && c_skill*c_skill*c_skill/10<c_exp && c_skill<101)
        {
                me->improve_skill("dodge",query("int", me));
                tell_object(me,"你的基本輕功進步了!\n");
        }
}