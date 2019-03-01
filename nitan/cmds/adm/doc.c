// doc.c

#include <ansi.h>
inherit F_CLEAN_UP;

int  help(object);
void QueryNpcInfo(string);
void QueryRoomInfo(string);
void QueryItemInfo(string);
string QuerySkill(object);
string QueryAction(object,object);
string QueryEquipProp(object,mapping);

int main(object me,string arg)
{
        string path,var;
        string *filename;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg,"%s %s", path, var) != 2)
        {
                return help(me);
        }

        if (file_size(path = resolve_path(query("cwd", me), path)) != -2)
                return notify_fail("羶衄涴跺醴翹ㄐ\n");

        seteuid(getuid());
        if (path[sizeof(path)-1] != '/')
                path += "/";

        switch(var)
        {
        case "-npc":
        case "-NPC":
                QueryNpcInfo(path);
                break;
        case "-room":
        case "-ROOM":
                QueryRoomInfo(path);
                break;
        case "-item":
        case "-ITEM":
                QueryItemInfo(path);
                break;
        default:
                write("統杅祥勤ㄛ笭陔怀ㄐ\n");
                break;
        }

        return 1;
}

void QueryNpcInfo(string path)
{
        string filename;
        string *file;
        object obj, me = this_player();
        int num = 0;

        filename = path + "恅紫寥濬眳NPC";

        if (file_size(filename) > 0)
                rm(filename);

        file = get_dir(path);
        foreach(string tmp in file)
        {
                if (file_size(tmp) == -2)
                        continue;
                write(sprintf("  淕燴ㄗ%-15sㄘ笢...", tmp));
                reset_eval_cost();
                obj = new(path + tmp);
                if (! objectp(obj))
                {
                        write(RED " ...囮啖ㄐ\n" NOR);
                        continue;
                }
                if( !obj->is_character() || !query("name", obj) )
                {
                        write(RED "NOT NPCㄐ\n" NOR);
                        continue;
                }
                num ++;
                write_file(filename, GRN "==================================================\n" NOR, 0);
                write_file(filename, RED "恅璃唗瘍ㄩ" NOR + num + "\n", 0);
                write_file(filename, RED "恅璃靡備ㄩ" NOR + tmp + "\n", 0);
                write_file(filename,WHT"笢恅靡趼ㄩ"NOR+query("name", obj)+"\n",0);
                write_file(filename, WHT "荎恅: " NOR + sprintf("%s", implode(obj->parse_command_id_list(), ",")) + "\n", 0);
                write_file(filename, QuerySkill(obj), 0);
                write_file(filename, "岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n");

                write_file(filename, sprintf("▽  儕  ▼%10d      ▽ 儕薯 ▼%d \n",
                                             query("max_jing", obj),query("max_jingli", obj)));
                write_file(filename, sprintf("▽    ▼%10d      ▽ 囀薯 ▼%d (+%d)\n",
                                             query("max_qi", obj),query("max_neili", obj),query("jiali", obj)));
                write_file(filename, sprintf("▽ 妘昜 ▼%10d      ▽ 夔 ▼%d \n",
                                             query("food", obj),query("potential", obj)));
                // write_file(filename, sprintf("▽ 窊阨 ▼%10d      ▽ 冪桄 ▼%s \n",
                //query("water", obj),query("combat_exp", obj)));


                destruct(obj);
                write(YEL " ...傖髡﹝ \n" NOR);
        }

        write_file(filename, "==================================================\n", 0);
        write_file(filename, "    掛醴翹狟軞僕衄" GRN + num + NOR "跺NPC恅璃ㄐ\n", 0);
        write("=========================================\n");
        write("      僕淕燴ㄗ"GRN + chinese_number(num) + NOR"ㄘ跺NPC恅璃   \n\n");
        me->start_more(read_file(filename, 1));
}

void QueryRoomInfo(string path)
{
        string filename;
        string *file;
        object obj;
        object finder = new("/clone/npc/trashcan");//睡珨跺(living object)
        object me = this_player();
        int num = 0;

        filename = path + "恅紫寥濬眳ROOM";

        if (file_size(filename) > 0)
                rm(filename);

        file = get_dir(path);
        foreach(string tmp in file)
        {
                if (file_size(path+tmp) == -2)
                        continue;

                write(sprintf("  淕燴ㄗ%-15sㄘ笢...", tmp));
                reset_eval_cost();
                obj = load_object(path + tmp);

                if (! objectp(obj))
                {
                        write(RED" ...囮啖ㄐ\n"NOR);
                        continue;
                }

                if (obj->is_character() || ! stringp(query("short", obj)))
                {
                        write(RED "NOT ROOM\n" NOR);
                        continue;
                }

                num ++;
                write_file(filename, "岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n", 0);
                write_file(filename, YEL "滇潔唗瘍ㄩ" WHT + num + "\n" NOR, 0);
                write_file(filename,YEL"滇潔靡備ㄩ"WHT+query("short", obj)+"("+tmp+")\n"NOR,0);
                write_file(filename,YEL"滇潔釴梓ㄩ"WHT"ㄗ"+query("coor/x", obj)+","+
                           query("coor/y", obj)+","+query("coor/z", obj)+"ㄘ\n"NOR,0);
                write_file(filename, QueryAction(obj, finder), 0);
                if( mapp(query("coor", obj)) )
                        write(YEL " ...傖髡\n" NOR);
                else
                        write(YEL " ...傖髡" RED "ㄗ拸釴梓ㄘ\n" NOR);
        }
        write_file(filename, "==================================================\n", 0);
        write_file(filename, "    掛醴翹狟軞僕衄" GRN + num + NOR "跺滇潔ㄐ\n", 0);
        write("=========================================\n");
        write("      僕淕燴ㄗ" GRN + chinese_number(num) + NOR"ㄘ跺滇潔恅璃   \n\n");
        me->start_more(read_file(filename, 1));
        destruct(finder);
}

void QueryItemInfo(string path)
{
        string filename;
        string *file;
        object obj;
        mapping prop;
        object me = this_player();
        int num = 0;
        int flag = 0;

        filename = path + "恅紫寥濬眳ITEM";

        if (file_size(filename) > 0)
                rm(filename);

        file = get_dir(path);
        foreach(string tmp in file)
        {
                if (file_size(path+tmp) == -2)
                        continue;

                write(sprintf("  淕燴ㄗ%-15sㄘ笢...", tmp));
                reset_eval_cost();
                obj = new(path + tmp);

                if (! objectp(obj))
                {
                        write(RED " ...囮啖ㄐ\n" NOR);
                        continue;
                }

                if (obj->is_character() || ! stringp(query("name", obj)))
                {
                        write(RED "NOT ITEM\n" NOR);
                        continue;
                }
                num ++;
                write_file(filename, GRN "岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n" NOR, 0);
                write_file(filename, WHT "昜唗瘍ㄩ" NOR + num + "\n", 0);
                write_file(filename,WHT"昜靡備ㄩ"NOR+query("name", obj)+"("+
                           implode(obj->parse_command_id_list(), ",") + ")\n", 0);
                write_file(filename,WHT"昜歎跡ㄩ"NOR+MONEY_D->price_str(query("value", obj))+"\n",0);
                /*
                if( mapp(prop=query("weapon_prop", obj)) )
                        QueryEquipProp(obj,prop);
                else
                if( mapp(prop=query("armor_prop", obj)) )
                        QueryEquipProp(obj,prop);
                */
                destruct(obj);
                write(YEL " ...傖髡﹝ \n" NOR);
        }
        write_file(filename, "==================================================\n", 0);
        write_file(filename, "    掛醴翹狟軞僕衄" GRN + num + NOR "跺昜ㄐ\n", 0);
        write("=========================================\n");
        write("      僕淕燴ㄗ" GRN + chinese_number(num) + NOR "ㄘ跺昜恅璃   \n\n");
        me->start_more(read_file(filename, 1));
}

string QueryAction(object ob,object finder)
{
        mixed *cmds;
        string msg = "", *str, name;
        int count = 0;

        if( stringp(query("short", ob)) )
                name=query("short", ob);
        else name=query("name", ob);

        finder->move(ob);
        cmds = finder->query_commands();

        if (sizeof(cmds) == 1)
                return("");

        msg += "          " CYN + name + "枑鼎狟硌鍔ㄩ\n" NOR;

        foreach(mixed cmd in cmds)
        {
                if (cmd[2] == finder) continue;

                msg += sprintf(WHT "%-10s   " NOR, cmd[0]);
                count++;
                if(count%4 == 0)
                        msg += "\n";
        }
        msg += "\n";
        return msg;
}
string QuerySkill(object ob)
{
        mapping m_skills, m_enable;
        string *sname;
        int i, jibie, lingwu, jilei, xiuwei, opt_all;
        string  msg = "";

        m_skills = ob->query_skills();
        if (! sizeof(m_skills))
                return("");

        msg += "          " + ob->name() + "醴垀悝徹腔撮夔ㄩ\n";
        m_enable = ob->query_skill_map();

        if (! mapp(m_enable))
                m_enable = ([]);

        sname = keys(m_skills);
        msg = msg + "岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n";

        for (i = 0; i < sizeof( m_skills ); i++)
        {
                msg = msg + sprintf("%s%-12s%-28s%8d\n",
                                    m_enable[ sname[i] ] ? WHT"ㄙ"NOR : "  ",
                                    to_chinese(sname[i]),  " □" + sname[i] + "■",
                                    m_skills[sname[i]]);
        }
        return msg;
}

string QueryEquipProp(object equip,mixed props)
{
        string type, msg = "";
        int *special_props, i;
        int count = 0;
        string *prop;

        if( stringp(type=query("skill_type", equip)) )
                msg += sprintf("條濬倰ㄩ%-10s     馴 僻 薯ㄩ%d",
                               type,query("weapon_porp/damage", equip));

        else
        if( stringp(type=query("skill_type", equip)) )
                msg += sprintf("滅撿濬倰ㄩ%-10s     滅 郘 薯ㄩ%d",
                               type,query("armor_porp/armor", equip));

        if (! sizeof(props)) return("");

        msg += "          " + equip->name() + "腔坻髡虴ㄩ\n";
        prop = keys(props);
        for (i = 0; i < sizeof(props); i++)
        {
                // foreach(string prop in props){
                if (prop[i] == "armor" || prop[i] == "damage")
                        continue;

                msg += sprintf(WHT "%-12d  " NOR, props[prop[i]]);
                if (i%4 == 0)
                        msg += "\n";
        }
        return msg;
}

int help(object me)
{
        write(@HELP
硌鍔跡宒ㄩdoc 繚噤靡 -笱濬靡
醴枑鼎腔笱濬衄ㄩroom﹜npc﹜item
瞰ㄩ
        doc /d/city/npc -npc
衄俙模婓盄奀郔疑祥妏蚚森硌鍔﹝
HELP);
        return 1;
}