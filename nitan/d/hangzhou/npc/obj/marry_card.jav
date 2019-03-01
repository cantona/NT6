// marry_card.c
#include <ansi.h>

inherit ITEM;
void create()
{
        set_name(RED"婚約"NOR, ({"marrycard"}) );
        set_weight(10);
        set("no_get",1);
        set("no_steal",1);
        set("no_drop","你的婚約不能丟棄,只能去紅娘莊解除婚約。\n");
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("material", "paper");
        }
}

void init()
{
        add_action("do_put","put");
        add_action("do_coupletalk", "coupletalk");
        add_action("do_coupletalk", "ct");
        add_action("do_cemote", "ce" );
}

int do_put(string arg)
{
        object me = this_player();
        if(arg!="marrycard in corpse") return 0;
        else
        {
          tell_object(me,"這是你最珍貴的東西，怎麼可以放到那兒去？\n");
          return 1;
        }
}

int do_cemote(string arg)
{
        object *list, me;
        object couple_ob;
        string target, tmpstr1, tmpstr2,str1,str2;
        string cardname;
        int i;

        me = this_player();
        list = all_inventory(this_player());
        i = sizeof(list);
        while (i--)
        {
              if( (query("id", list[i])) == "marrycard" )
                cardname=query("name", list[i]);
        }

        if (sscanf(cardname,"你和%s的婚約" ,target)!=1)
                return notify_fail("你沒有伴侶.\n");

        couple_ob = find_player(target);
        if( !couple_ob )
          return notify_fail("你的伴侶現在聽不見你，或者已經離開遊戲了。\n");
        if( query("gender", couple_ob) != "女性" )
        {
                tmpstr1 = "老婆"; tmpstr2 = "老公";
                str1 = "她"; str2 = "他";
        } else
        {
                tmpstr1 = "老公"; tmpstr2 = "老婆";
                str1 = "他"; str2 = "她";
        }

        if (!arg)
        {
                write( MAG "你又深情的想念你的愛侶了。\n" NOR);
                tell_room(environment(me), CYN+(string)me->name()+
                "又深情的想念"+str1+"的愛侶"+ (string)couple_ob->name()+
                "了。\n" +NOR, ({me, couple_ob}));
                tell_object(couple_ob, sprintf(MAG "%s %s
                又在深情的想你了\n"NOR, tmpstr1,me->name(1) ));
                return 1;
        }
        if (environment(me) == environment(couple_ob ) )
        {
           if (arg == "kiss")
           {
              write( MAG "你擁住你的愛侶，深深的一吻，許久...許久...\n" NOR);
              tell_room(environment(me), CYN+(string)me->name()+
              "擁住"+(string)couple_ob->name()+"，深深的一吻。\n"
                +NOR, ({me, couple_ob}));
                tell_object(couple_ob, sprintf(MAG "%s %s
                擁住你，深深的一吻，許久...許久...\n"NOR,tmpstr1,me->name(1)));
           }
        }

        return 1;
}

int do_coupletalk(string arg)
{
        object *list, me;
        object couple_ob;
        string target, tmpstr1, tmpstr2;
        string cardname;
        int i;

        me = this_player();
        list = all_inventory(this_player());
        i = sizeof(list);
        while (i--)
        {
              if( (query("id", list[i])) == "marrycard" )
                cardname=query("name", list[i]);
        }

        if (sscanf(cardname,"你和%s的婚約" ,target)!=1)
                return notify_fail("你沒有伴侶.\n");

        couple_ob = find_player(target);
        if( !couple_ob )
           return notify_fail("你的伴侶現在聽不見你，或者已經離開遊戲了。\n");
        if( query("gender", couple_ob) != "女性" )
        {
                tmpstr1 = "老婆";
                tmpstr2 = "老公";
        } else
        {
                tmpstr1 = "老公";
                tmpstr2 = "老婆";
        }

        write(sprintf(MAG"你對%s %s 說：%s\n"NOR,
                tmpstr2,couple_ob->name(1), arg ));
        tell_object(couple_ob, sprintf(MAG "%s %s 對你說：%s\n"NOR,
               tmpstr1,me->name(1), arg ));

        return 1;
}

void owner_is_killed()
{
        object me = this_player();
        write(HIW"屍體中的婚卡化為雲煙消失了……\n"NOR);
        destruct(this_object());
}

string query_autoload()
{
        object *list, me;
        object couple_ob;
        string target,cardname;
        int i;

        me = this_player();
        list = all_inventory(this_player());
        i = sizeof(list);
        while (i--)
        {
              if( (query("id", list[i])) == "marrycard" )
                cardname=query("name", list[i]);
        }

        sscanf(cardname,"你和%s的婚約" ,target);
        return target;
}

void autoload(string arg)
{
        int i;
        object couple_ob;
        object me;
        string tmpstr, tmpstr1;

//        me = this_player();
        couple_ob = find_player(arg);
        if (couple_ob)
        {
             if( query("gender", couple_ob) != "女性" )
             {
                    tmpstr1 = "老公";
                    tmpstr = "老婆";
              } else
              {
                    tmpstr1 = "老婆";
                    tmpstr = "老公";
              }
              write(sprintf( MAG "你的%s也在這裡，快去找啦...\n"NOR,tmpstr1));
              tell_object(couple_ob ,
              sprintf( MAG "你的%s來啦,快去接...\n" NOR, tmpstr));
//me->name(1)+"("+me->query("id")+")",environment(me))->query("name") );
        }
        set("name","你和"+arg+"的婚約");
}