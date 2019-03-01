#include <ansi.h> 
inherit ROOM;

void init();
int close_gate();
int do_open();
int valid_leave();
string look_gate();

void create()
{
            set("short", "廣場");
        set("long", @LONG
這裡是少林寺前的廣場，整個廣場由大塊的青石舖成，極為平坦。
但因年代久遠，都有些破損。叢叢小草從石板的縫隙中長了出來。廣
場的周圍都是密密的鬆樹林，四角上各放了幾塊石碑，字跡都甚為模
糊。正前方黃牆碧瓦，飛檐翹檁，正中一道二丈來寬，三丈來高的朱
紅杉木包銅大門(gate)。上方一塊大匾，龍飛鳳舞地書著『少林寺』
三個大字。寺前三三兩兩的站著幾個僧人。
LONG );
            set("exits", ([
                "east" : __DIR__"guangchang1e",
                "south" : __DIR__"shijie11",
                "west" : __DIR__"guangchang1w",
            ]));

            set("outdoors", "shaolin");
           set("item_desc",([
                "gate"        :    (: look_gate :),
            ]));

            set("objects",([
                CLASS_D("shaolin") + "/qing-fa" : 1,
            ]));

            setup();
            "/clone/board/shaolin_b"->foo();
}


/* TODO
 此處改為：(knock gate) 敲門後一僧人應聲打開大門：
“吱”的一聲，大門打了開來，一位壯年僧人上上下下打量了你
（他，她，人名） 一會，
（如為本寺僧人，且無罪過，正神提高或無增減）側身讓開，說道：師兄辛苦了，請進。
（如為本寺僧人，正神降低或有負神）沉下臉來，說道：戒律院主持玄痛大師請師兄火
　　　　　　　　　　　　　　　　　　　　　　　　　速去戒律院陳述此行過犯。
　　　　　　　　　　　　　　　　　（直接送交戒律院處治查問後，打入僧監關押）。
（如非本寺僧人，男性，有正神）說道：這位施主請回罷，本寺不接待俗人。
（如非本寺僧人，女性，有正神）說道：這位女施主還是請回罷，本寺從不接待女客。
（如非本寺僧人，無論男女，有負神）立時從身畔摯出一把雪亮的戒刀來，把明晃晃的
　　　　　　　　　　　　　　　　　刀尖對準你的胸口，橫眉怒目地說道：你等邪魔
　　　　　　　　　　　　　　　　　外道，還不給我滾開！以後再敢走近少林一步，
　　　　　　　　　　　　　　　　　我立時就斬斷你們的狗腿！
對不起，俗家弟子不得入寺修行
*/

void init()
{
            add_action("do_knock", "knock");
}

int close_gate()
{
            object room;

            if (! (room = find_object(__DIR__"smdian")))
                room = load_object(__DIR__"smdian");

            if (objectp(room))
            {
                delete("exits/north");
                message("vision", HIY "只聽乒地一聲，裡面有人把大門關上了。\n" NOR,
                                      this_object());

                delete("exits/south", room);
                if (objectp(present("qingfa biqiu", room)))
                            message("vision", CYN "清法比丘上前把大門關了起來。\n" NOR, room);
                else
                            message("vision", CYN "壯年僧人上前把大門關了起來。\n" NOR, room);
            } else
                message("vision", "ERROR: gate not found(close).\n", room);

            return 1;
}

int do_knock(string arg)
{
            object room;

            if (query("exits/north"))
                return notify_fail("大門已經是開著了。\n");

            if (! arg || (arg != "gate" && arg != "north"))
                return notify_fail("你要敲什麼？\n");

            if (! (room = find_object(__DIR__"smdian")))
                room = load_object(__DIR__"smdian");

            if (objectp(room))
            {
                set("exits/north", __DIR__"smdian");
                message_vision(HIY "$N" HIY "輕輕地敲了敲門，只聽吱地"
                               "一聲，衣位壯年僧人應聲打開大門。\n" NOR,
                               this_player());

                set("exits/south", __FILE__, room);
                message("vision", HIY "外面傳來一陣敲門聲，壯年僧人應"
                                  "聲上前把大門開。\n" NOR, room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
            }
            return 1;
}

int valid_leave(object me, string dir)
{
            if (dir != "north")
                return ::valid_leave(me, dir);

            if (! ::valid_leave(me, dir))
                return 0;

            if( (query("family/family_name", me) == "少林派") )
            {
                if( query("class", me) != "bonze" )
                {
                            return notify_fail(CYN "壯年僧人說道：對不起，俗家弟子不得"
                                           "入寺修行。\n" NOR);
                }

                if( (query("guilty", me) == 0) && 
                    (query("combat/K_record", me) == query("combat/WPK", me)) )
                {
                            write(CYN "壯年僧人側身讓開，說道：師兄辛苦了，請進。\n" NOR);
                            return 1;
                } else
                {
                            if( query("guilty", me) == 0 )
                            {
                                if( query("combat/shen_record", me)>query("shen", me) )
                                            set("guilty", 1, me);
                                        else
                                            set("guilty", 2, me);
                                set("combat/K_record",query("combat/WPK",  me), me);
                                set("combat/shen_record",query("shen",  me), me);
                        }

                            me->move(__DIR__"smdian");
                            write(CYN "壯年僧人沉下臉來，說道：戒律院主持玄痛大師請師兄去戒律院"
                                     "陳述此行過犯。\n" NOR);
                            return -1;
                }
            } else
        if (present("yingxiong ling", me))
            {
                write(CYN "壯年僧人合十為禮，側身讓開，說道：原來是貴客駕到，請進請進。\n" NOR);
                return 1;
            }
    
            if( query("shen", me) >= 0 )
            {
                if( query("gender", me) == "女性" )
                {
                            return notify_fail(CYN "壯年僧人說道：這位女施主還是請回罷，本寺"
                                           "從不接待女客。\n" NOR);
                } else
                {
                            return notify_fail(CYN "壯年僧人說道：這位施主請回罷，本寺不接待"
                                           "俗人。\n" NOR);
                }
            }
            return notify_fail(HIR "壯年僧人立時從身畔摯出一把雪亮的戒刀來，把明晃晃的刀尖對"
                           "準你的\n胸口，橫眉怒目地說道：“你等邪魔外道，還不給我滾開！"
                           "以後再敢走\n近少林一步，我立時就斬斷你們的狗腿！”\n\n" NOR);

}

string look_gate()
{
            return YEL "一道三丈來高的朱紅杉木包銅大門。\n" NOR;
}