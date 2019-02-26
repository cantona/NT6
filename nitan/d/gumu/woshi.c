// Room: /d/gumu/woshi.c
// Last Modifyed by Winder on Jan. 14 2002

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIC"卧室"NOR);
        set("long", @LONG
這裏是小龍女居住的卧室，房中空空洞洞。右首是一塊長條青石作
牀 (bed)，牀上鋪了張草蓆，一幅白布當作薄被，此外除了一根人高的
繩索橫過室中，室左立着一個粗糙木櫥(chu)。
LONG        );
        set("item_desc", ([
                "bed" : HIC"一張由普通青石鋪成的牀，牀角落處，有一塊突起的石板，似可扳動。\n"NOR, 
                "chu" : HIY"一座普通之極的櫥子。\n"NOR, 
        ]));
        set("exits", ([
                "east" : __DIR__"mudao15",
        ]));
        set("chu", 1);
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", -40);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_tang", "tang");
        add_action("do_ban", "ban");
        add_action("do_open","kai");
        add_action("do_open","open");
        add_action("do_xian","xian");
}

int do_tang(string arg)
{
        object me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if ( arg == "bed")
        {
                message_vision(HIC"$N俯附身躺在青石製成的石牀上面。\n"NOR,me);
                set_temp("marks/牀", 1, me);
                return 1;
        }
        return notify_fail("你要躺在地上，小心着涼哦！\n");
}  

int do_ban(string arg)
{  
        object me=this_player();

        if( !query_temp("marks/牀", me) )
                return notify_fail("你沒躺牀上，恐怕用不上力吧！\n");        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if ( arg == "shiban" || arg == "stone")
        {
                if( query("neili", me)<500 )
                        return notify_fail("你使出吃奶的勁力，但石板卻紋絲不動。\n");
                message_vision(HIY "$N用力扳動突起的石板，只聽得軋軋幾響，石牀已落入下層石室。\n"NOR,me);
                addn("neili", -200, me);
                delete_temp("marks/牀", me);
                me->move(__DIR__"shishi0");
                write(HIY"室頂石壁又慢慢自行推上了。\n"NOR);
                return 1;
        }
        return notify_fail("你要扳什麼？\n");
}

int do_open(string arg)
{
        object ob, me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if ( arg=="chu")
        {
                if ( query("chu") == 1 )
                {
                        if(!objectp(present("gold key", me)))        
                                return notify_fail("你沒有鑰匙，怎麼開啊？\n");
                        message_vision("$N慢慢用金鑰匙打開了櫥門。\n",me);
                        ob=new(__DIR__"obj/box");
                        ob->move(environment(me));
                        write("你發現櫥內放着個長方形的鐵盒子。\n");
                        set("chu", 0);
                        return 1;
                }
                else
                {
                        write("你來晚了，櫥門現在開着呢。\n");
                        return 1;
                }
        }
        return notify_fail("你要開什麼？\n");
}

int do_xian(string arg)
{
        object suo, me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if ( arg =="box" || arg=="da tiehe" || arg =="tiehe")
        {
                if(!(present("da tiehe", environment(me)))) 
                        return notify_fail("這裏有鐵盒麼？\n");
                if(!objectp( present("silver key", me)))        
                        return notify_fail("你沒有鑰匙，用什麼開啊？\n");
                delete_temp("marks/鐵盒", me);
                message_vision("$N用銀鑰匙開了鎖，輕輕掀開了鐵盒。\n",me);
                suo=new(__DIR__"obj/yinsuo");
                if(!clonep(suo))
                        return notify_fail("你來晚了，盒子裏面空無一物。\n");
                write("掀開鐵盒，你發現裏面放着一團冰綃般的物事。\n");
                suo->move(me);                
                return 1;
        }
        return notify_fail("你要掀開什麼？\n");
}
