inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "深潭");
        set("long",
"[1;32m周圍一片黑暗，大概已經深入地底了吧。藉著苔蘚發出的幽\n"
"幽磷光，可以看到前方不遠處有一個深潭(tan)，寒氣逼人。\n"
);
        set("exits", ([ 
       "eastup" : __DIR__"spirit6",
        ]) );


        set("no_magic", 1);
        setup();
}


void init()
{
        add_action("do_look", "look");
        add_action("do_approach", "approach");
}

int do_look(string arg)
{
        object me;
        object room;
        me = this_player();
        if(!arg || arg != "深潭" && arg != "tan" ) return 0;
        switch ( random (2)) {
                case 0:
tell_object(me,"潭邊長滿了苔蘚，還是不要靠（ａｐｐｒｏａｃｈ）的太近。\n"); 
                break;
                case 1:
message_vision("$N探頭向潭裡望去。 \n", me); 
tell_object(me,"黑不隆咚的潭水深不見底。 \n");
                break;
        }


        return 1;
}
int do_approach(string arg)
{
        object me;
        object room;
        me = this_player();
        if(!arg || arg != "深潭" && arg != "tan" ) return 0;
        switch ( random (3)) {
                case 0:
message_vision("$N走近深潭探頭向裡望去。 \n", me); 
tell_object(me,"潭水深不見底，不過你似乎可以聽到底下流水的聲音。 \n");
                break;
                case 1:
message_vision("$N走近深潭探頭向裡望去。哎呀！一不小心掉了進去！\n", me); 
message_vision("$N的頭撞在潭壁上，一下子昏了過去！\n", me); 
                call_out("be_saved",8);
                me->unconcious();
                room = find_object(__DIR__"spirit10");
                 if(!objectp(room)) room=load_object(__DIR__"spirit10");
                me->move(room);
                break;
                case 2:
message_vision("$N走近深潭探頭向裡望去。哎呀！一不小心掉了進去！\n", me);
              room = find_object(__DIR__"underwater");
                if(!objectp(room)) room=load_object(__DIR__"underwater");
                me->move(room);
                break;
        }

        return 1;
}

int be_saved()
{   
            object me;            me=this_player();

            me->remove_call_out("revive");
            me->revive();
            me->reincarnate();
message_vision("$N慢慢清醒過來，發現自己在一間小屋中！\n", me); 
message_vision("一個美麗的精靈族女子看見$N恢復了知覺，關切地走了過來！\n", me);
           return 1;
}
