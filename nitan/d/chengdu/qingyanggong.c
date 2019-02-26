#include <ansi.h>
inherit ROOM;

int do_open(string arg);
int do_knock(string arg);
int do_back();

void create()
{
        set("short", "青羊宮");
        set("long", @LONG
青羊宮是天下第一大道觀。觀中林木婆娑，冠蓋亭亭觀中道士匆
匆來去，沒人得空理你，更沒人接待你。你覺得到一種寬鬆的失落。
旁邊有一個木門（door）。
LONG );
        set("exits", ([
                "northeast" : __DIR__"westroad1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("item_desc", ([
                "door" : "厚厚的木門緊關着，有些年歲了。\n" ,
        ]));        
        set("no_clean_up", 0);
        set("coor/x", -15250);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( query("family/family_name", me) == "峨嵋派" )
        {
                tell_object(me, HIG "\n你突然發現峨嵋派弟子留在此處的"
                                "密信。\n" NOR);
                set_temp("want_leave", 1, me);

                remove_call_out("letter");
                call_out("letter", 3, me);
        }
        add_action("do_back",  "back");
        add_action("do_knock", "knock");
        add_action("do_open", "open");
}

void letter(object me)
{
        if (! objectp(me))
                return;

        if( !query_temp("want_leave", me) )
                return;

        tell_object(me, WHT "  ┏━━━━━━┓\n"
                            "  ┃觀旁樹林內有┃\n"
                            "  ┃本派密道能夠┃\n"
                            "  ┃直通(" HIY "back" NOR + WHT ")峨┃\n"
                            "  ┃嵋華藏庵大殿┃\n"
                            "  ┗━━━━━━┛\n" NOR);
}

int do_back()
{
        object me = this_player();

        if( query_temp("want_leave", me) )
        {
                message("vision", HIC "忽然間只見" + me->name() + HIC
                                  "身形一晃，竟沒了蹤影。\n" NOR,
                                  environment(me), ({me}));
                me->move("/d/emei/midao5");
                tell_object(me, HIC "\n你鑽進了青羊觀樹林內的密道。\n\n" NOR);
        }
        return 1;
}

int do_open(string arg)
{
        if(arg=="door")
        return notify_fail("你用力拉了拉木門，結果一點動靜都沒有，看來是被反鎖了！\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("你要敲什麼？\n");
          if (arg != "door")
                return notify_fail("你要敲什麼？\n");
          if( arg=="door" ) {
                message_vision("$N試著敲了敲木門。\n", me);
                if( query("bunch/bunch_name", me) != "修羅門" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“是來投靠咱們修羅門的吧！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move(__DIR__"xlm_cdfb");
                        return 1;
                }
                if( good_bunch(me) || (query("bunch/bunch_name", me) != "修羅門" && query("shen", me)>0) )
                { 
                                command("say 哪裏來的邪魔歪道，找打麼？\n"); 
                        return 1; 
                } 
                message_vision("木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“既然是本門的兄弟，就進來吧！”，
説完一把把$N拉了進去。\n",me);
                me->move(__DIR__"xlm_cdfb"); 
                return 1; 
        }
        
        return 1;
}