// meeting_room.c

#include <ansi.h>
#include <command.h>
inherit ROOM;

#define SAY_CMD         "/cmds/std/say"

int do_start(string arg);
int do_say(string msg);
int do_over();
int do_not();

void create()
{
        set("short", "巫師會議室");
        set("long", @LONG
這裏就是泥潭巫師的會議室所在。剛粉刷過的四周牆壁上掛着泥
潭㈠ 巫師畫像，分別有：高處不勝寒(lonely)、擇明(ken)、安全中
心(sinb)；泥潭㈡巫師畫像：高處不勝寒(lonely)、一人兩角(yezh)；
泥潭㈢ 巫師畫像：高處不勝寒(lonely)、風飛(wind)。 屋子的正中
央放着一張楠木桌椅，是泥潭巫師組用來開會用的。
LONG );

        set("exits", ([ 
                "down" : __DIR__"wizard_room",
        ]));

        set("valid_startroom", 1);
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_clean_up", 0);

        set("coor/x", 10000);
        set("coor/y", 10000);
        set("coor/z", 10010);
        setup();

        call_other("/clone/board/meet_b", "???");
}

void init()
{
        add_action("do_say", "say");
        add_action("do_say", "'");
        add_action("do_start", "start");
        add_action("do_over", "over");
        add_action("do_not", "tell");
        add_action("do_not", "replay");
        add_action("do_not", "whisper");
        add_action("do_not", "kickout");
        add_action("do_not", "goto");
        add_action("do_not", "call");
        add_action("do_not", "flyto");
        add_action("do_not", "home");
        add_action("do_not", "dual");  
        add_action("do_not", "dest"); 
        add_action("do_not", "quit");      
}


int do_start(string arg)
{
        object me;

        me = this_player();

        if (wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("對不起，您無權召開巫師會議。\n");

        if ((int)query("meeting_trigger") != 0)
                return notify_fail("會議正在進行中。\n");

        set("meeting_trigger", 1);

        foreach (object player in users())
        {
                if (! wizardp(player))
                        continue;
                        
                if (player == me)
                        continue;

                tell_object(player, sprintf(GRN "%s(%s)告訴你：巫師會議現在召開，請到巫師會議室開會。\n" NOR, 
                                            query("name", me),query("id", me)));
                                            
                player->move("/d/wizard/meeting_room.c");
                message_vision("$N準時到達了會場。\n", player);       
                set_temp("disable_type", HIW"<會議中>"NOR, player);
        }

        set_temp("keeper", 1, me);
        
        message_vision(HIW "\n$N大聲宣佈：“會議現在開始。”\n" NOR, me);

        log_file("meeting.log", sprintf("%s(%s) start the meeting on %s.\n", 
                                        me->name(1), geteuid(me),
                                        ctime(time())));     
        return 1;
}

int do_say(string msg)
{
        if (! msg) return 0;

        SAY_CMD->main(this_player(), msg);
        
        if ((int)query("meeting_trigger") == 1)        
                log_file("meeting.log", sprintf(CYN "%s(%s)説道：" + msg + "\n" NOR,
                                                this_player()->name(1), 
                                                query("id", this_player())));
        return 1;
}

int do_over()
{
        object *ob, me;
        int i;
        string wiz_status;
        me = this_player();
        
        if (! wizardp(me) || wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("你沒有權力終止會議。\n");
                
        if ((int)query("meeting_trigger") == 0)
                return notify_fail("現在沒有進行任何會議。\n");
        
        delete("meeting_trigger");
 
        foreach (object player in users())
        {
                if (! wizardp(player))
                        continue;
                        
                if( query_temp("disable_type", player) == HIW"<會議中>"NOR )
                        delete_temp("disable_type", player);
        }
        
        message_vision(HIW "\n$N大聲宣佈：“會議現在結束。”\n" NOR, me);
        log_file("meeting.log", sprintf("%s(%s) over the meeting on %s.\n", 
                                        me->name(1), geteuid(me), 
                                        ctime(time())));
        return 1;
}

int do_not()
{
       if (query("meeting_trigger"))
       {
               write("請專心開會！\n");
               return 1;
       }
       return 0;
}

int valid_leave(object me, string dir)
{
        if (query("meeting_trigger"))
                return notify_fail("現在正在開會呢，你最好哪裏也不要去。\n");
                
        return ::valid_leave(me, dir);
}
