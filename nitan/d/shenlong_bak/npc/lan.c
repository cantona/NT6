// /d/shenlon/npc/lan.c
// Last Modified by winder on Jul. 12 2002

inherit NPC;
string ask_me(object who);

void create()
{
        set_name("藍鳳凰", ({ "lan fenghuang", "lan" }));
        set("shen_type", 0);

        set("str", 20);
        set("con", 20);
        set("dex", 22);
        set("gender", "女性");
        set("age", 20);
        set("long","她就是雲南五毒教教主藍鳳凰，一生守身如玉，從來不對任何男子假以辭色。\n");
        set("combat_exp", 30000);
        set("max_qi", 500);
        set("max_jing", 500);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 20);
        set_skill("poison", 80);
        set_skill("force", 80);
        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/damage", 40);

        set("attitude", "friendly");
        set("inquiry", ([
                "五毒教" : "哼！就憑你也來打聽本教？\n",
                "藍鳳凰" : "你瞎了眼啦？\n",
                "藥方" : "我五毒教祖傳眾多古怪藥方，但向來秘而不宣。\n",
                "五仙藥酒" : (: ask_me :),
        ]));

        setup();
        carry_object("/d/city/obj/necklace")->wear();
        carry_object(CLOTH_DIR"cloth/feature")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
}

string ask_me(object who)
{
        object me = this_player();
        string myid=query("id", me);

        if( query("combat_exp", me)<100000){
                command("laugh " + myid);
                command("kick " + myid);
                return "還不快滾！本教主不殺無名小卒。\n";
        }
        say("藍鳳凰頓時臉色一變，怒斥道：這五仙大補藥酒，乃當世最神奇的補藥，豈能落在你輩手中！\n");
        set("attitude", "aggressive");
        kill_ob(me);
        return "藍鳳凰大喝一聲，叫道：“本教主今天豁出去，跟你拼了。”\n";
}

void unconcious()
{
        object ob;

        say("\n突然藍鳳凰一聲長嘆，掏出一瓶藥酒扔入舟外。\n");
        say("隨即慘淡一笑，正欲再摸出什麼物事，但終究無力動彈不得。\n");
        ob = new("/d/shenlong/obj/yaofang");
        ob->move(this_object());
        ::unconcious();
}

void die()
{
        object ob;

        say("\n突然，只見船身一晃，藍鳳凰一腳踩空掉入河裡。\n");
        if( ob = present("yaofang", this_object()) ) destruct(ob);
        destruct(this_object());
}
