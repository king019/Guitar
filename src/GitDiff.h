#ifndef GITDIFF_H
#define GITDIFF_H

#include <set>
#include "misc.h"
#include "Git.h"
#include "GitObjectManager.h"

class GitDiff {
	friend class CommitListThread;
public:
private:
	class LookupTable;
private:
//	GitPtr g;
	GitObjectCache *objcache = nullptr;
	QList<Git::Diff> diffs;

	bool interrupted = false;

	struct Interrupted {
	};

	void checkInterrupted()
	{
		if (interrupted) {
			throw Interrupted();
		}
	}

	typedef std::list<LookupTable> MapList;

	GitPtr git();

//	void diff_tree_(GitPtr g, QString const &dir, QString older_commit_id, QString newer_commit_id);
//	void commit_into_map(GitPtr g, const TreeItemList *files, MapList const *diffmap);
//	void parseTree_(GitPtr g, GitObjectCache *objcache, QString const &dir, QString const &id, std::set<QString> *dirset, MapList *path_to_id_map)
//	{
//		if (!dir.isEmpty()) {
//			auto it = dirset->find(dir);
//			if (it != dirset->end()) {
//				return;
//			}
//			dirset->insert(dir);
//		}

//		TreeItemList files;
//		parse_tree_(g, objcache, id, dir, &files);
//		path_to_id_map->push_back(LookupTable());
//		LookupTable &map = path_to_id_map->front();
//		for (TreeItem const &cd : files) {
//			map.store(cd.name, cd.id);
//		}
//	}
	static void AddItem(Git::Diff *item, QList<Git::Diff> *diffs);

	void retrieveCompleteTree(const QString &dir, const GitTreeItemList *files, std::map<QString, GitTreeItem> *out);
	void retrieveCompleteTree(const QString &dir, const GitTreeItemList *files);
public:
	GitDiff(GitPtr g, GitObjectCache *objcache)
	{
//		this->g = g;
		this->objcache = objcache;
	}

	bool diff(QString id, QList<Git::Diff> *out);
	bool diff_uncommited(QList<Git::Diff> *out);

	void interrupt()
	{
		interrupted = true;
	}

public:
	static QString diffFile(GitPtr g, const QString &a_id, const QString &b_id);
	static void parseDiff(const QString &s, const Git::Diff *info, Git::Diff *out);
	static QString makeKey(QString const &a_id, QString const &b_id);
	static QString makeKey(const Git::Diff &diff);
	static QString prependPathPrefix(const QString &path);


};

#endif // GITDIFF_H
