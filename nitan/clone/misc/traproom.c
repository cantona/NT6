// Room: /clone/room/traproom.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit ROOM;

void falldown(object);
void flydown(object);
int do_jump(string);
int do_climb(string);
int do_push(string);
int do_fill();
void maintaining(object, int);
int trap_power(object);

void create()
{
        set("short",HIR "陷阱" NOR);
        set("long", HIR @LONG
這是一口不知是誰挖掘的陷阱。陷阱深達數丈，由下往上望去，只
能見到桌面般大的一片天空。陷阱周圍是鬆軟的土層，不停地往外滲水。
似乎剛剛挖好沒多久。
LONG NOR
);      
        set("invalid_startroom",1);
        set("trap_room",1);
        setup();
        call_out("maintaining", 30, this_object(), 0);
}

void init()
{
        int depth, power, reward;
        object me = this_player();
        object roomtrap = this_object();
        object owner=query("owner", roomtrap);

        depth=query("depth", roomtrap);
        power = trap_power(me);

        if( query_temp("is_riding", me))delete_temp("is_riding", me);
        remove_call_out("maintaining");
        call_out("maintaining", 30, roomtrap, 0);

        if( depth>power && owner != me && query("limit", roomtrap) && 
                !query_temp("trap/" + file_name(roomtrap), me) )
        {
                me->set_temp("trap/"+file_name(roomtrap));
                call_out("falldown", 1, me);

                if( objectp(owner) && userp(me) &&
                        environment(owner) == roomtrap &&
                        query("limit", roomtrap) >= 1 )
                {
                        reward=query("combat_exp", me)/300;
                        if( reward >= 40 ) reward = 40;
                        addn("combat_exp", reward, owner);

                        reward=query("shen", me)/300;
                        if( reward >= 10 ) reward = 10;
                        addn("shen", -reward, owner);
                }
                if( query("limit", roomtrap) >= 1)addn("limit", -1, roomtrap);
                if( depth / 5 > power ) me->unconcious();
        }
        else call_out("flydown", 1, me);
// tell_object(me, HIY "power = " + power + "\n" NOR);

        add_action("do_jump", "tiao");
        add_action("do_climb", "pa");
        add_action("do_push", "tui");
        add_action("do_fill", "tian");

        add_action("do_jump", "jump");
        add_action("do_climb", "climb");
        add_action("do_push", "push");
        add_action("do_fill", "fill");
}

void falldown(object me)
{
        object rum_ob;
        object owner=query("owner", this_object());

// To noisy. 
        if( !objectp(rum_ob = find_object("/d/city/npc/aqingsao")) )
                rum_ob = load_object("/d/city/npc/aqingsao");
        CHANNEL_D->do_channel(rum_ob, "rumor",
                sprintf("%s掉進陷阱裏了。", me->name(1)));
//
        message("vision", HIY "只聽哇地一聲喊，從上邊掉下一團黑影來！\n" NOR, environment(me), me);
        tell_object(me, HIR "你只覺得腳下一虛，大叫一聲，摔了下去！\n" NOR);
        me->start_busy(3+random(5));
        if( present(owner, environment(me)))
        {
                owner->start_busy(3+random(5));
        }
}

void flydown(object me)
{       
        if( random(5) == 0 )
        message("vision", "只見人影一閃，" + me->name() + "已經站在你的面前！\n", environment(me), me);
}

int valid_leave(object me, string dir)
{
        int power, depth;
        mapping exit;
        object roomtrap = this_object();

        if( query("owner", roomtrap) == me)return ::valid_leave(me,dir);
        if( query("race", me) == "飛禽")return ::valid_leave(me,dir);
//      if( !roomtrap->query("limit") )         return ::valid_leave(me, dir);

        depth=query("depth", roomtrap);
        power = trap_power(me);
        if(me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if( depth / 3 > power )
        {
                return notify_fail("陷阱太深了，你怎麼闖也闖不出去，看來得請人來把你推（ＴＵＩ）出去了。\n");
        }
        else
                if( depth / 2 > power)
                {
                        return notify_fail("陷阱很深，你得試試能不能爬（ＰＡ）出去。\n");
                }
                else
                        if( depth > power )
                        {
                                return notify_fail("陷阱看來挺深的，你得試試能不能使勁跳（ＴＩＡＯ）出去。\n");
                        }
                        
                        else if( !mapp(exit=query("exits", roomtrap)) || !stringp(exit[dir]) )
       {
         return notify_fail("這個方向沒有路。\n");
       }
                        else
                        {
                                me->receive_damage("qi", depth/20, "在陷阱裏累死了");
                                message_vision("$N長袖飄飄，姿態美妙地從陷阱上方飛躍而過。\n", me);
                                return ::valid_leave(me, dir);
                        }
}

int do_jump(string arg)
{
        int depth, power;
        object me, roomtrap, roomto;

        me = this_player();
        roomtrap = this_object();

        depth=query("depth", roomtrap);
        power = trap_power(me);

        if( !arg || !query("exits/"+arg, environment(me)) )
                return notify_fail("你要往哪個方向跳越？\n");
        if( !(roomto=find_object(query("exits/"+arg, roomtrap))) )
                roomto=load_object(query("exits/"+arg, roomtrap));
        if( depth < power )
                return notify_fail("以你的本領，用得着這麼費事嗎？\n");
        if(me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
        if( depth>power && depth/2<power && query("qi", me) >= depth/10 )
        {
                me->receive_damage("qi", depth/10, "在陷阱裏累死了");
                if( random(me->query_kar() + me->query_dex()) >= 15 )
                {
                        me->move(roomto);
                        message_vision("$N展開輕功，猛一縱身，嗖地從陷阱裏躍了出去。\n", me);
                        return 1;
                }
                else
                {
                        message_vision("$N使勁猛地一跳，半空中一口氣接不上來，又重重地摔了下來。\n", me);
                        return 1;
                }
        }
        else return notify_fail("你有這個力氣嗎？\n");

        if( depth / 2 > power && depth / 3 < power )
        return notify_fail("看來跳是不成的了，試試能不能爬上去？\n");
        return notify_fail("陷阱太深了，看來一定得喊人來救你出去了。\n");
}

int do_climb(string arg)
{
        int depth, power;
        object me, roomtrap, roomto;

        me = this_player();
        roomtrap = this_object();

        depth=query("depth", roomtrap);
        power = trap_power(me);

        if( !arg || !query("exits/"+arg, environment(me)) )
                return notify_fail("你要沿哪個方向爬上去？\n");
        if( !(roomto=find_object(query("exits/"+arg, roomtrap))) )
                roomto=load_object(query("exits/"+arg, roomtrap));
        if( depth < power )
                return notify_fail("以你的本領，用得着這麼費事嗎？\n");
        if( depth > power && depth / 2 < power )
                return notify_fail("陷阱並不深，不妨施展輕功，試試能不能跳上去？\n");
        if(me->is_busy()) return notify_fail("你現在正忙着呢。\n");
        if( depth/2>power && depth/3<power && query("qi", me) >= depth/5 )
        {
                me->receive_damage("qi", depth/5, "爬陷阱累死了");
                if( random(me->query_kar() + me->query_str()) >= 15 )
                {
                        me->move(roomto);
                        message_vision("$N抓住陷阱邊上的草根和樹枝，手腳並用地慢慢爬了出去。\n", me);
                        return 1;
                }
                else
                {
                        message_vision("$N慢慢地往上爬着爬着，忽然坪的一聲，狼狽不堪地摔了下來。\n", me);
                        return 1;
                }
        }
        else return notify_fail("你有這個力氣嗎？\n");
        return notify_fail("陷阱太深了，看來一定得喊人來救你出去了。\n");
}

int do_push(string arg)
{
        object me, ob, roomtrap, roomto;
        int depth, power_me, power_ob;
        string who, where;

        me = this_player();
        roomtrap = this_object();

        if( !arg || sscanf(arg, "%s %s", who, where)!=2 ) 
                return notify_fail("指令格式：tui <人物> <方向>\n");
        if( !objectp(ob = present(who, environment(me))) || !living(ob))
                return notify_fail("你要推誰上去？\n");
        if( query("id", me) == who )
                return notify_fail("自己推自己上去？好像不行吧。\n");

        depth=query("depth", roomtrap);
        power_me = trap_power(me);
        power_ob = trap_power(ob);

        if( !query("exits/"+where, environment(me)) )
                return notify_fail("你要沿哪個方向推"+ob->name()+"上去？\n");
        if( !(roomto=find_object(query("exits/"+where, roomtrap))) )
                roomto=load_object(query("exits/"+where, roomtrap));
        if( depth>power_me || query("qi", me)<depth/5 )
                return notify_fail("你沒這個本事推"+ob->name()+"上去吧？\n");
        if(me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
        me->receive_damage("qi", depth/5, "救人出陷阱時累死了");
        if( random(me->query_str() + ob->query_kar()) >= 15 )
        {
                ob->move(roomto);
                me->move(roomto);
                message_vision("$N輕輕托起$n，鼓足內力，一下就把$n送出了陷阱。接着一縱身，自己也躍了出去。\n", me, ob);
                return 1;
        }
        else
        {
                message_vision("$N托住$n想把$n送出陷阱，結果$N手一軟，兩人都摔倒在地。\n", me, ob);
                return 1;
        }
        return notify_fail("陷阱太深了，看來得另想辦法。\n");
}

int do_fill()
{
        object me, roomtrap, roomto, roomfrom, *inv;
        int depth, power_me, i;

        me = this_player();
        roomtrap = this_object();
        roomfrom=query("roomfrom", roomtrap);
        roomto=query("roomto", roomtrap);

        depth=query("depth", roomtrap);
        power_me = trap_power(me);

        if( (depth*2>power_me || query("qi", me)<depth/3) && 
                me != query("owner", roomtrap) )
                return notify_fail("這個陷阱太深了，想填住它，非累死不可。\n");
        me->receive_damage("qi", depth/3, "填陷阱時累死了");
        message_vision("$N滿頭大汗地挑泥擔水，把陷阱嚴嚴實實地填了起來。\n\n", me);
        set("exits/"+query("from", roomtrap), file_name(roomto), roomfrom);
        set("exits/"+query("to", roomtrap), file_name(roomfrom), roomto);
        delete("exits/jump"+query("from", roomtrap), roomfrom);
        delete("exits/jump"+query("to", roomtrap), roomto);
        
        inv = all_inventory(environment(me));

        if( sizeof(inv) >= 1 )
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        if( !living(inv[i]) || inv[i] == me ) continue;
                        else inv[i]->move(roomto);
                }
        }

        me->move(roomto);
        destruct(roomtrap);

        return 1;
}

int trap_power(object me)
{
        return  me->query_skill("dodge")*5
                + me->query_dex()*4
                + me->query_int()*3
                + me->query_kar()*2
                +query("qi", me);
}

void maintaining(object roomtrap, int count)
{
        object owner, roomfrom, roomto;
  int i;
  object *inv;
        roomfrom=query("roomfrom", roomtrap);
        roomto=query("roomto", roomtrap);

        if( objectp(owner=query("owner", roomtrap)) && count<10 )
        { 
/*                if( environment(owner) == roomtrap ||
                        environment(owner) == roomfrom ||
                        environment(owner) == roomto )
                        count = 0;
                else */count++;
                call_out("maintaining", 120, roomtrap, count);
        }
        else
        {
                set("exits/"+query("from", roomtrap), file_name(roomto), roomfrom);
                set("exits/"+query("to", roomtrap), file_name(roomfrom), roomto);
                delete("exits/jump"+query("from", roomtrap), roomfrom);
                delete("exits/jump"+query("to", roomtrap), roomto);
                inv=all_inventory(roomtrap);
    tell_room(roomtrap,"這時候走過來一箇中年漢子，見你掉在陷阱裏面，就找了條繩子把你拉了上來。\n隨後你們一起把這個害人的陷阱嚴嚴實實地填了起來。\n");
                for (i=0;i<sizeof(inv);i++)
                        if (!living(inv[i])) continue;
                        else inv[i]->move(roomfrom);
                destruct(roomtrap);
        }
}
