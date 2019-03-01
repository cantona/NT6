// named.c 保存所有玩家的名字

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

nosave string *family_name = ({ "東方", "獨孤", "慕容", "歐陽", "司馬",
                                "西門", "尉遲", "長孫", "諸葛", "上官",
                                "夏候", "聞人", "皇甫", "澹台", "公治",
                                "淳于", "申屠", "公孫", "公羊", "軒轅",
                                "令狐", "鐘離", "宇文", "幕容", "仲孫",
                                "司徒", "司空", "端木", "公良", "百裡",
                                "東郭", "南郭", "呼延", "羊舌", "東門",
                                "南官", "南宮", "拓拔", "完顏", "耶律",
                                "鮮于" });

void create()
{
        seteuid(getuid());
        restore();
}

void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// the name PATH store in dbase
#define PATH(name)      (name[0..1] + "/" + name)

// remove the mapping of a name & id
public void remove_name(string name, string id)
{
        string old;
        string *ms;

        if (! stringp(name) || strlen(name) < 2 ||
            undefinedp(old = query(PATH(name))))
                return;

        if (! stringp(old) ||
            ! sizeof(ms = explode(old, "/") - ({ id })))
        {
                delete(PATH(name));
                if (! sizeof(query(name[0..1])))
                        delete(name[0..1]);
                save();
                return;
        }

        set(PATH(name), implode(ms, "/"));
        save();
}

// record the mapping of a name & id
public void map_name(string name, string id)
{
        string old;
        string *ms;

        if (! stringp(name) || strlen(name) < 2)
                return;

        if (! stringp(old = query(PATH(name))))
                set(PATH(name), id);
        else
        {
                ms = explode(old, "/");
                if (member_array(id, ms) != -1)
                        // alreay exist
                        return;

                ms += ({ id });
                set(PATH(name), implode(ms, "/"));
        }

        save();
}

// check name
public string who_is(string name)
{
        string id;

        if (! stringp(name) || strlen(name) < 2 ||
            ! stringp(id = query(PATH(name))))
                return "沒有人叫這個名字。\n";

        return "遊戲中叫" + name + "的有：" + id + "\n";
}

// check the id - name
private int really_exist(string name, string id)
{
        object ob;
        object user;
        int result;

        if (! stringp(id))
                return 0;

        ob = find_player(id);
        if (objectp(ob))
        {
                if (ob->name(1) == name)
                        return 1;
                else
                        return 0;
        }

        // read the data of user object
        ob = new(LOGIN_OB);
        set("id", id, ob);
        user = LOGIN_D->make_body(ob);
        destruct(ob);

        if (! objectp(user))
                // no such user
                return 0;

        result = user->restore() && (user->name(1) == name);
        destruct(user);

        return result;
}

// assure the id matched the name
public void assure_map_name(string name)
{
        string id;
        string *ids;

        if (! stringp(id = query(PATH(name))))
                // null name
                return;

        ids = explode(id, "/");

        // examine all the id
        ids = filter_array(ids, (: really_exist, name :));

        if (! sizeof(ids))
        {
                // no id matched
                delete(PATH(name));
                return;
        }

        // reset name-id mapping
        id = implode(ids, "/");
        set(PATH(name), id);
}

// If the name to be a new name, dose it invalid ?
public string invalid_new_name(string name)
{
        string id;
        int i;
        int l;

        if (! stringp(name) || strlen(name) < 2)
                return "不能使用空名字。\n";

        if (member_array(name, family_name) != -1)
                return "不能使用復姓作為名字。\n";

        // 和對有關ID-名字的信息
        assure_map_name(name);

        if (id = query(PATH(name)))
                return "這個名字和 " + id + " 的名字重復了。\n";

        if (strlen(name) < 4)
                return 0;

        l = strlen(name);
        for (i = 0; i <= l - 4; i++)
        {
                // 和對有關ID-名字的信息
                assure_map_name(name[i..i + 3]);
                if (i + 6 <= l)
                        assure_map_name(name[i..i + 5]);

                if (member_array(name[i..i + 3], family_name) == -1 &&
                    stringp(id = query(PATH(name[i..i + 3]))))
                        return "這個名字和 " + id + " 的名字太接近了。\n";

                if ((i + 6 <= l) &&
                    stringp(id = query(PATH(name[i..i + 5]))))
                        return "這個名字和 " + id + " 的名字太接近了。\n";
        }

        return 0;
}

// change a user's name
public varargs string change_name(object me, string new_name, int force)
{
        string result;
        mapping dbase;

        if (stringp(me->name(1)))
        {
                remove_name(me->name(1),query("id", me));
                result = invalid_new_name(new_name);
        } else
                result = 0;

        if (force || ! result)
        {
                dbase = me->query_entire_dbase();
                dbase["name"] = new_name;
        }
        
        map_name(me->name(1),query("id", me));
        return result;
}

// how many name
public int query_total_name()
{
        string *ks;
        int total;
        int i;

        total = 0;
        ks = keys(query_entire_dbase());
        for (i = 0; i < sizeof(ks); i++)
                total += sizeof(query(ks[i]));

        return total;
}

string query_save_file() { return DATA_DIR "named"; }