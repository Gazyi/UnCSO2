#ifndef PKGFILESYSTEMMODEL_H
#define PKGFILESYSTEMMODEL_H

#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QPersistentModelIndex>
#include <QSet>
#include <QVariant>

class CCSO2PkgEntry;
class CMainWindow;
class CPkgFileSystemNode;

class CPkgFileSystemModel : public QAbstractItemModel
{
	Q_OBJECT

public:	   
	explicit CPkgFileSystemModel( CMainWindow* pParent = Q_NULLPTR );
	~CPkgFileSystemModel();

	QVariant data( const QModelIndex &index, int role ) const Q_DECL_OVERRIDE;
	bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) Q_DECL_OVERRIDE;

	QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;

	QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const Q_DECL_OVERRIDE;
	QModelIndex index( const CPkgFileSystemNode *node, int column = 0) const;

	QModelIndex parent( const QModelIndex &index ) const Q_DECL_OVERRIDE;

	int rowCount( const QModelIndex &parent = QModelIndex() ) const Q_DECL_OVERRIDE;
	int columnCount( const QModelIndex &parent = QModelIndex() ) const Q_DECL_OVERRIDE;

	Qt::ItemFlags flags( const QModelIndex &index ) const Q_DECL_OVERRIDE;

	void sort( int column, Qt::SortOrder order = Qt::AscendingOrder ) Q_DECL_OVERRIDE;
	void sortChildren( int column, const QModelIndex &parent );

	CPkgFileSystemNode* GetNode( const QModelIndex &index ) const; 	

	bool GenerateFileSystem();
	void CleanFileSystem();
	void CreateChild( CCSO2PkgEntry* pPkgEntry );
	bool ExtractCheckedNodes();		

	inline bool WasGenerated() { return m_bGenerated; }		

	inline bool ShouldDecryptEncFiles() { return m_bShouldDecryptEncFiles; }
	inline void SetDecryptEncFiles( bool bShouldDecryptEncFiles ) { m_bShouldDecryptEncFiles = bShouldDecryptEncFiles; }
	inline bool ShouldRenameEncFiles() { return m_bShouldRenameEncFiles; }
	inline void SetRenameEncFiles( bool bShouldRenameEncFiles ) { m_bShouldRenameEncFiles = bShouldRenameEncFiles; }
	inline bool ShouldDecompVtfFiles() { return m_bShouldDecompVtfFiles; }
	inline void SetDecompVtfFiles( bool bShouldDecompVtfFiles ) { m_bShouldDecompVtfFiles = bShouldDecompVtfFiles; }
	inline bool ShouldDecompBspFiles() { return m_bShouldDecompBspFiles; }
	inline void SetDecompBspFiles( bool bShouldDecompBspFiles ) { m_bShouldDecompBspFiles = bShouldDecompBspFiles; }
	inline bool ShouldReplaceShadowblock() { return m_bShouldReplaceShadowblock; }
	inline void SetReplaceShadowblock( bool bShouldReplaceShadowblock ) { m_bShouldReplaceShadowblock = bShouldReplaceShadowblock; }
	inline bool ShouldFixBspLumps() { return m_bShouldFixBspLumps; }
	inline void SetFixBspLumps( bool bShouldFixBspLumps ) { m_bShouldFixBspLumps = bShouldFixBspLumps; }

	enum
	{
		FileNameColumn = 0,
		TypeColumn,
		PackedSizeColumn,
		UnpackedSizeColumn,
		NumColumns
	};

private:	
	void UpdateNodeChildren( const QModelIndex &index, const QVariant &value );
	bool DecryptEncFile( std::filesystem::path& szFilePath, uint8_t*& pBuffer, uint32_t& iBufferSize );
	bool IsFileContentEncrypted( uint8_t* pFileBuffer, uint32_t iBufferSize );

	static QVector<CPkgFileSystemNode*> m_DirectoryNodes;

	CMainWindow* m_pParentWindow;

	CPkgFileSystemNode* m_pRoot;
	QSet<QPersistentModelIndex> m_CheckedIndexes;		
	
	int m_iSortColumn;
	Qt::SortOrder m_SortOrder;	 	
	bool m_bForceSort;

	bool m_bGenerated;		 
	
	bool m_bShouldDecryptEncFiles;
	bool m_bShouldRenameEncFiles;
	bool m_bShouldDecompVtfFiles;
	bool m_bShouldReplaceShadowblock;
	bool m_bShouldDecompBspFiles;
	bool m_bShouldFixBspLumps;
};

#endif // PKGFILESYSTEMMODEL_H
