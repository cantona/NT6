// key.c
#include <ansi.h>
inherit ITEM;
int is_key() {return 1;}

void create()
{
        set_name("私房鑰匙", ({"key", "yaoshi"}));
        set("long",
                "這是一把桃花村私人住宅的鑰匙。
可以用來開門(unlock)和關門(lock)。\n");
        set("unit", "把");
        set("weight", 10);
        set("no_put",1);
        set("no_get",1);
        set("no_drop",1);
}

string query_autoload() { return 1 + ""; }        //autoload weapon
void init()
{
        add_action("do_lock","lock");
        add_action("do_unlock","unlock");
}

int do_unlock()
{
        object table, bottle, rose, room, here, me = this_player();
  object *rooms;
  int i;
  if (!present(this_object(), this_player()))
    return 0;

        if( !query("home", me) )
                return notify_fail("你沒私宅呀，在這開什麼開！\n");
        if( query("short", environment(me)) != "桃花坪" )
                return notify_fail("你的私宅在桃花谷裏桃花坪上！\n");
        rooms = children("/d/taohuacun/obj/player");
        for (i=0;i < sizeof(rooms);i++)
        {
                if( query("owner", rooms[i]) == query("id", me) )
                 {room=rooms[i];break;}
        }
        if (i == sizeof(rooms))
        {
                seteuid(getuid());
                room = new("/d/taohuacun/obj/player");
          set("short",query("home/home_name",  me), room);
          set("long",query("home/home_desc",  me)+"\n", room);
    set("owner",query("id",  me), room);
          table = new("/d/taohuacun/obj/table");
          bottle = new("/d/taohuacun/obj/bottle");
          rose = new("/d/taohuacun/obj/rose");
          rose -> move(bottle);
          bottle -> move(table);
          table -> move(room);
        }
          if(!( here = find_object("/d/taohuacun/taohua5")) )
                  here = load_object("/d/taohuacun/taohua5");
          set("exits/enter", file_name(room), here);
          set("exits/out", "/d/taohuacun/taohua5", room);
//        set("sleep_room", "1");
        set("sleep_room", "1", room);
        message_vision(HIG "$N掏出鑰匙，輕輕一旋，舉手推開房門。\n" NOR,me);
        return 1;
}
int do_lock()
{
        object here;
  object me=this_player();
  object room;
  int i,flag;
  object *inv;
  if (!present(this_object(), this_player()))
    return 0;
        if( query("owner", environment(me)) != query("id", me )
          && query("short", environment(me)) != "桃花坪" )
                return notify_fail("你的私宅在桃花谷裏桃花坪上！\n");

        if(!( here = find_object("/d/taohuacun/taohua5")) )
                here = load_object("/d/taohuacun/taohua5");
        if( query("exits/enter", here) && 
        room=find_object(query("exits/enter", here)) )
        {
                 flag=1;
                 inv=all_inventory(room);
                 for(i=0;i<sizeof(inv);i++)
                  {
                            if (userp(inv[i]))
                            {flag=0;break;}
                          }
                  if (flag) destruct(room);
        delete("exits/enter", here);
        message_vision(HIG "只聽得碰的一聲響，$N把房門關上了。\n" NOR, this_player());
        }
        else
        {return notify_fail("門沒有開着啊。\n");}
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}