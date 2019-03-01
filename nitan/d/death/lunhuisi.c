#include <ansi.h>
#include <room.h>
inherit ROOM;

void check_trigger();
void close_passage();
void reset();

void create()
{
        set("short", HIB "【輪回司】" NOR);
        set("long", HIB @LONG

                    輪         回         司

    輪回司內寒氣森森，青石舖設的地面滿是灰塵。堂周青布圍幔，圍幔
上用金銀絲線繡著些奇怪的圖案，正堂上一張青石桌案 (table)，桌案上
布滿了蛛網，看樣子很久沒打掃過了。

LONG NOR );

        set("item_desc", ([
                "table" : WHT "一個青石制成的桌案，上面有幾許"
                          "裂縫，看樣子已擱在這裡很久了。\n" NOR,
        ]));

        set("exits", ([
                "out" : __DIR__"lunhuisi_road1",
        ]));

        create_door("out", YEL "銅門" NOR, "enter", DOOR_CLOSED);
        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_turn", "turn");
        add_action("do_say", "say");
        add_action("do_move", "move");
        add_action("do_move", "push");
        add_action("do_move", "pull");
}

int do_move(string arg)
{
        string dir;

        if( ! arg || arg == "" ) return 0;

        if( arg == "table" )
        {
                write(HIY "\n你用盡了全身力氣想移動石桌，可是它猶如在地面"
                      "生根一般，紋絲不動。\n" NOR);
                return 1;
        }
}

void check_trigger()
{
        object room;

        if( (int)query("zuo") == 3
        && (int)query("you") == 3
        && ! query("exits/down") )
        {
                message("vision", WHT "\n石桌忽然「軋軋軋」一陣響動，向"
                                  "一側緩緩移開，石桌下豁然露出一個黑"
                                  "洞洞的階梯。\n" NOR, this_object() );
                set("exits/down", __DIR__"diyin_road1");
                delete("zuo");
                delete("you");
                remove_call_out("close_passage");
                call_out("close_passage", 10);
        }
}

void close_passage()
{
        object room;

        if( ! query("exits/down") ) return;
        message("vision", WHT "\n石桌忽然「軋軋軋」一陣響動，緩緩地移回"
                          "原處，將向下的階梯蓋了個嚴實。\n" NOR,
                          this_object() );
        delete("exits/down");
}


int do_turn(string arg)
{
        string dir;

        if( !arg || arg=="" ) return 0;

        if( arg == "lunpan" && (int)query("poem_said") == 1 )
        {
                write(HIC "你試著觸動輪盤，發現它可以左右轉動。\n" NOR);
                return 1;
        }

        if( sscanf(arg, "lunpan %s", dir) == 1 && (int)query("poem_said") == 1 )
        {
                if( dir == "left" )
                {
                        message_vision(HIW "$N" HIW "將輪盤向左轉動了一圈"
                                       "……忽然「喀喀喀」幾聲輕響，輪盤又"
                                       "轉了回原位。\n" NOR, this_player());
                        addn("zuo", 1);
                        check_trigger();
                        return 1;
                }
                if( dir == "right" )
                {
                        message_vision(HIR "$N" HIR "將輪盤向右轉動了一圈"
                                       "……忽然「喀喀喀」幾聲輕響，輪盤又"
                                       "轉了回原位。\n" NOR, this_player());
                        addn("you", 1);
                        check_trigger();
                        return 1;
                }
           else {
                        write(HIC "你要將輪盤向著哪個方向轉動？\n" NOR);
                        return 1;
                }
        }
}

int do_say(string arg)
{
        string dir;

        if( ! arg || arg == "" ) return 0;

        if( arg == "天地崩裂時" && (int)query("poem_said") != 1 )
        {
                message_vision(HIW "\n只聽$N" HIW "猛然高聲喝道：“天地崩"
                               "裂時！”\n" NOR + HIR "\n$N" HIR "話音剛"
                               "落，地面突然「轟隆隆」晃動了幾下。青石桌案"
                               "表層的石屑登時脫落，露出了一個石盤。\n\n"
                               NOR, this_player());
                this_object()->recreate();
                set("poem_said", 1);
                return 1;
        }

        if( arg == "天地崩裂時" && (int)query("poem_said") == 1 )
        {
                write(HIC "\n你對著大堂一聲猛喝，聲音在司內回盪了好一陣才消逝。\n" NOR);
                return 1;
        }
}

void reset()
{
        ::reset();
        delete("zuo");
        delete("you");
}

void recreate()
{
        set("short", HIB "【輪回司】" NOR);
        set("long", HIB @LONG

                    輪         回         司

    輪回司內寒氣森森，青石舖設的地面滿是灰塵。堂周青布圍幔，圍幔
上用金銀絲線繡著些奇怪的圖案，正堂上一張青石桌案 (table)，桌案的
表層已經脫落，露出內部的一個石制輪盤(lunpan)。

LONG NOR );

        set("item_desc", ([
                "table" : WHT "一個青石制成的桌案，上面有幾許"
                          "裂縫，它的表層已經脫落了。\n" NOR,
                "lunpan": WHT "一個石制的輪盤，上面滿是花紋，似"
                          "乎可以轉動。\n" NOR,
        ]));

        set("exits", ([
                "out" : __DIR__"lunhuisi_road1",
        ]));

        create_door("out", YEL "銅門" NOR, "enter", DOOR_CLOSED);
        set("no_magic", 1);
        setup();
}