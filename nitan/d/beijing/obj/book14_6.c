// book14_6.c
inherit ITEM;
int do_tear(string arg);
#include <ansi.h>;
void init()
{
        add_action("do_tear", "tear");
}

void create()
{
        set_name(HIR"四十二章經六"NOR, ({"book6"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "\n一本正紅旗的經書，封皮(binding)很精緻。\n");
                set("unit", "本");
                set("material", "paper");
        }
        setup();
}

int do_tear(string arg)
{
        object me;
        string dir;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if(!present(this_object(), me))
                return notify_fail("你要撕什麼？\n");

        if(arg=="book6")
        {
                message_vision("$N一下把經書撕得粉碎。\n", me);
                destruct(this_object());
                return 1;
        }

        if( sscanf(arg, "book6 %s", dir)==1 )
        {
                if( dir=="binding" )
                {
                        if( query("hasgot", this_object()) )
                                message_vision("$N將封皮撕開，發現羊皮已經被取走了。\n", me);
                        else
                        {
                                message_vision("$N將封皮撕開，幾塊羊皮掉了下來。\n", me);
                                message_vision("$N先將羊皮上的地圖記了下來，然後把它們燒掉了。\n", me);
                                set("huanggong\haspi6", 1, me);
                                set("hasgot", 1, this_object());
                        }
                }
                else
                {
                        message_vision("$N一下把經書撕得粉碎。\n", me);
                        destruct(this_object());
                }
                return 1;
        }        
}