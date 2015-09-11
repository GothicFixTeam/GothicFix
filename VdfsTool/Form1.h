#pragma once


namespace VdfsTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TreeView^  FileTree;
	private: System::Windows::Forms::Button^  AddFolderButton;
	private: System::Windows::Forms::FolderBrowserDialog^  AddFolderDialog;
	private: System::Windows::Forms::Button^  NewFolderButton;
	private: System::Windows::Forms::Button^  AddFilesButton;
	private: System::Windows::Forms::OpenFileDialog^  AddFilesDialog;


	private: System::Windows::Forms::SaveFileDialog^  SaveFileDialog;
	private: System::Windows::Forms::Button^  DeleteButton;
	private: System::Windows::Forms::Button^  SaveButton;


	private: System::Windows::Forms::TextBox^  CommentBox;

	private: System::Windows::Forms::Label^  CommentLabel;
	private: System::Windows::Forms::Button^  OpenButton;
	private: System::Windows::Forms::OpenFileDialog^  OpenFileDialog;
	private: System::Windows::Forms::DateTimePicker^  TimeStampPicker;
	private: System::Windows::Forms::Label^  TimeStampLabel;
	private: System::Windows::Forms::Label^  StatusLabel;
	private: System::Windows::Forms::Button^  ClearButton;
	private: System::Windows::Forms::Button^  ExtractButton;
	private: System::Windows::Forms::FolderBrowserDialog^  ExtractFolderDialog;
	private: System::Windows::Forms::SaveFileDialog^  ExtractFileDialog;
	private: System::Windows::Forms::Button^  RenameButton;
	private: System::Windows::Forms::ImageList^  TreeViewImages;


	private: System::ComponentModel::IContainer^  components;

	protected: 

	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->FileTree = (gcnew System::Windows::Forms::TreeView());
			this->TreeViewImages = (gcnew System::Windows::Forms::ImageList(this->components));
			this->AddFolderButton = (gcnew System::Windows::Forms::Button());
			this->AddFolderDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->NewFolderButton = (gcnew System::Windows::Forms::Button());
			this->AddFilesButton = (gcnew System::Windows::Forms::Button());
			this->AddFilesDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SaveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->DeleteButton = (gcnew System::Windows::Forms::Button());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->CommentBox = (gcnew System::Windows::Forms::TextBox());
			this->CommentLabel = (gcnew System::Windows::Forms::Label());
			this->OpenButton = (gcnew System::Windows::Forms::Button());
			this->OpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->TimeStampPicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->TimeStampLabel = (gcnew System::Windows::Forms::Label());
			this->StatusLabel = (gcnew System::Windows::Forms::Label());
			this->ClearButton = (gcnew System::Windows::Forms::Button());
			this->ExtractButton = (gcnew System::Windows::Forms::Button());
			this->ExtractFolderDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->ExtractFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->RenameButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// FileTree
			// 
			this->FileTree->AllowDrop = true;
			this->FileTree->HideSelection = false;
			this->FileTree->ImageIndex = 0;
			this->FileTree->ImageList = this->TreeViewImages;
			this->FileTree->LabelEdit = true;
			this->FileTree->Location = System::Drawing::Point(12, 12);
			this->FileTree->Name = L"FileTree";
			this->FileTree->SelectedImageIndex = 0;
			this->FileTree->Size = System::Drawing::Size(844, 666);
			this->FileTree->TabIndex = 0;
			this->FileTree->AfterLabelEdit += gcnew System::Windows::Forms::NodeLabelEditEventHandler(this, &Form1::FileTree_AfterLabelEdit);
			this->FileTree->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::FileTree_DragDrop);
			this->FileTree->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::FileTree_DragEnter);
			this->FileTree->BeforeLabelEdit += gcnew System::Windows::Forms::NodeLabelEditEventHandler(this, &Form1::FileTree_BeforeLabelEdit);
			// 
			// TreeViewImages
			// 
			this->TreeViewImages->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"TreeViewImages.ImageStream")));
			this->TreeViewImages->TransparentColor = System::Drawing::Color::Fuchsia;
			this->TreeViewImages->Images->SetKeyName(0, L"dir.bmp");
			this->TreeViewImages->Images->SetKeyName(1, L"file.bmp");
			// 
			// AddFolderButton
			// 
			this->AddFolderButton->Location = System::Drawing::Point(999, 12);
			this->AddFolderButton->Name = L"AddFolderButton";
			this->AddFolderButton->Size = System::Drawing::Size(132, 23);
			this->AddFolderButton->TabIndex = 1;
			this->AddFolderButton->Text = L"Add Folder";
			this->AddFolderButton->UseVisualStyleBackColor = true;
			this->AddFolderButton->Click += gcnew System::EventHandler(this, &Form1::AddFolderButton_Click);
			// 
			// AddFolderDialog
			// 
			this->AddFolderDialog->ShowNewFolderButton = false;
			// 
			// NewFolderButton
			// 
			this->NewFolderButton->Location = System::Drawing::Point(862, 41);
			this->NewFolderButton->Name = L"NewFolderButton";
			this->NewFolderButton->Size = System::Drawing::Size(131, 23);
			this->NewFolderButton->TabIndex = 2;
			this->NewFolderButton->Text = L"New Folder";
			this->NewFolderButton->UseVisualStyleBackColor = true;
			this->NewFolderButton->Click += gcnew System::EventHandler(this, &Form1::NewFolderButton_Click);
			// 
			// AddFilesButton
			// 
			this->AddFilesButton->Location = System::Drawing::Point(862, 12);
			this->AddFilesButton->Name = L"AddFilesButton";
			this->AddFilesButton->Size = System::Drawing::Size(131, 23);
			this->AddFilesButton->TabIndex = 3;
			this->AddFilesButton->Text = L"Add Files";
			this->AddFilesButton->UseVisualStyleBackColor = true;
			this->AddFilesButton->Click += gcnew System::EventHandler(this, &Form1::AddFilesButton_Click);
			// 
			// AddFilesDialog
			// 
			this->AddFilesDialog->AddExtension = false;
			this->AddFilesDialog->FileName = L"Add files";
			this->AddFilesDialog->Filter = L"All files|*.*";
			this->AddFilesDialog->Multiselect = true;
			this->AddFilesDialog->RestoreDirectory = true;
			this->AddFilesDialog->SupportMultiDottedExtensions = true;
			// 
			// SaveFileDialog
			// 
			this->SaveFileDialog->Filter = L"Virtual data file|*.vdf";
			// 
			// DeleteButton
			// 
			this->DeleteButton->Location = System::Drawing::Point(862, 70);
			this->DeleteButton->Name = L"DeleteButton";
			this->DeleteButton->Size = System::Drawing::Size(131, 23);
			this->DeleteButton->TabIndex = 4;
			this->DeleteButton->Text = L"Delete";
			this->DeleteButton->UseVisualStyleBackColor = true;
			this->DeleteButton->Click += gcnew System::EventHandler(this, &Form1::DeleteButton_Click);
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(999, 684);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(132, 23);
			this->SaveButton->TabIndex = 5;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &Form1::SaveButton_Click);
			// 
			// CommentBox
			// 
			this->CommentBox->Location = System::Drawing::Point(862, 523);
			this->CommentBox->MaxLength = 256;
			this->CommentBox->Multiline = true;
			this->CommentBox->Name = L"CommentBox";
			this->CommentBox->Size = System::Drawing::Size(268, 112);
			this->CommentBox->TabIndex = 7;
			// 
			// CommentLabel
			// 
			this->CommentLabel->AutoSize = true;
			this->CommentLabel->Location = System::Drawing::Point(862, 507);
			this->CommentLabel->Name = L"CommentLabel";
			this->CommentLabel->Size = System::Drawing::Size(54, 13);
			this->CommentLabel->TabIndex = 8;
			this->CommentLabel->Text = L"Comment:";
			// 
			// OpenButton
			// 
			this->OpenButton->Location = System::Drawing::Point(862, 684);
			this->OpenButton->Name = L"OpenButton";
			this->OpenButton->Size = System::Drawing::Size(131, 23);
			this->OpenButton->TabIndex = 9;
			this->OpenButton->Text = L"Open";
			this->OpenButton->UseVisualStyleBackColor = true;
			this->OpenButton->Click += gcnew System::EventHandler(this, &Form1::OpenButton_Click);
			// 
			// OpenFileDialog
			// 
			this->OpenFileDialog->Filter = L"Virtual data file|*.vdf";
			// 
			// TimeStampPicker
			// 
			this->TimeStampPicker->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->TimeStampPicker->Location = System::Drawing::Point(862, 658);
			this->TimeStampPicker->Name = L"TimeStampPicker";
			this->TimeStampPicker->Size = System::Drawing::Size(269, 20);
			this->TimeStampPicker->TabIndex = 10;
			// 
			// TimeStampLabel
			// 
			this->TimeStampLabel->AutoSize = true;
			this->TimeStampLabel->Location = System::Drawing::Point(862, 642);
			this->TimeStampLabel->Name = L"TimeStampLabel";
			this->TimeStampLabel->Size = System::Drawing::Size(63, 13);
			this->TimeStampLabel->TabIndex = 11;
			this->TimeStampLabel->Text = L"TimeStamp:";
			// 
			// StatusLabel
			// 
			this->StatusLabel->AutoSize = true;
			this->StatusLabel->Location = System::Drawing::Point(12, 689);
			this->StatusLabel->Name = L"StatusLabel";
			this->StatusLabel->Size = System::Drawing::Size(22, 13);
			this->StatusLabel->TabIndex = 12;
			this->StatusLabel->Text = L"OK";
			// 
			// ClearButton
			// 
			this->ClearButton->Location = System::Drawing::Point(999, 70);
			this->ClearButton->Name = L"ClearButton";
			this->ClearButton->Size = System::Drawing::Size(131, 23);
			this->ClearButton->TabIndex = 13;
			this->ClearButton->Text = L"Clear";
			this->ClearButton->UseVisualStyleBackColor = true;
			this->ClearButton->Click += gcnew System::EventHandler(this, &Form1::ClearButton_Click);
			// 
			// ExtractButton
			// 
			this->ExtractButton->Location = System::Drawing::Point(862, 100);
			this->ExtractButton->Name = L"ExtractButton";
			this->ExtractButton->Size = System::Drawing::Size(131, 23);
			this->ExtractButton->TabIndex = 14;
			this->ExtractButton->Text = L"Extract";
			this->ExtractButton->UseVisualStyleBackColor = true;
			this->ExtractButton->Click += gcnew System::EventHandler(this, &Form1::ExtractButton_Click);
			// 
			// ExtractFileDialog
			// 
			this->ExtractFileDialog->Filter = L"All files|*.*";
			// 
			// RenameButton
			// 
			this->RenameButton->Location = System::Drawing::Point(999, 40);
			this->RenameButton->Name = L"RenameButton";
			this->RenameButton->Size = System::Drawing::Size(131, 23);
			this->RenameButton->TabIndex = 15;
			this->RenameButton->Text = L"Rename";
			this->RenameButton->UseVisualStyleBackColor = true;
			this->RenameButton->Click += gcnew System::EventHandler(this, &Form1::RenameButton_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1139, 718);
			this->Controls->Add(this->RenameButton);
			this->Controls->Add(this->ExtractButton);
			this->Controls->Add(this->ClearButton);
			this->Controls->Add(this->StatusLabel);
			this->Controls->Add(this->TimeStampLabel);
			this->Controls->Add(this->TimeStampPicker);
			this->Controls->Add(this->OpenButton);
			this->Controls->Add(this->CommentLabel);
			this->Controls->Add(this->CommentBox);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->DeleteButton);
			this->Controls->Add(this->AddFilesButton);
			this->Controls->Add(this->NewFolderButton);
			this->Controls->Add(this->AddFolderButton);
			this->Controls->Add(this->FileTree);
			this->MaximumSize = System::Drawing::Size(1155, 757);
			this->MinimumSize = System::Drawing::Size(1155, 757);
			this->Name = L"Form1";
			this->Text = L"VdfsTool";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: TreeNode^ BuildDirTree(System::IO::DirectoryInfo^ dir) 
		 {
			 TreeNode^ Root = gcnew TreeNode(dir->Name);
			 cli::array<System::IO::DirectoryInfo^>^ Dirs = dir->GetDirectories();
			 for(System::Int32 i = 0; i < Dirs->GetLength(0); i++)
			 {
				 if(!Dirs[i]->Name->Contains(L" "))
					Root->Nodes->Add(BuildDirTree(Dirs[i]));
				 else
					StatusLabel->Text = L"Dir contains spaces!";
			 }
			 cli::array<System::IO::FileInfo^>^ Files = dir->GetFiles();
			 for(System::Int32 i = 0; i < Files->GetLength(0); i++)
			 {
				 if(!Files[i]->Name->Contains(L" "))
				 {
					 TreeNode^ file = Root->Nodes->Add(Files[i]->Name);
					 file->ImageKey = L"file.bmp";
					 file->SelectedImageKey = L"file.bmp";
					 file->Tag = Files[i]->FullName;
				 }
				 else
					StatusLabel->Text = L"Dir contains spaces!";
			 }
			 return Root;
		 }
private: System::Void MergeDirTrees(TreeNode^ base, TreeNode^ add) 
		 {
			 TreeNode^ Found;
			 for(IEnumerator^ Node = base->Nodes->GetEnumerator(); !Found && Node->MoveNext();)
			 {
				 if(!System::String::Compare(((TreeNode^)Node->Current)->Text, add->Text, true))
				 {
					 Found = (TreeNode^)Node->Current;
					 Found->Tag = add->Tag;
				 }
			 }
			 if(Found)
			 {
				 for(IEnumerator^ Node = add->Nodes->GetEnumerator(); Node->MoveNext();)
					 MergeDirTrees(Found, (TreeNode^)Node->Current);
			 }
			 else
				 base->Nodes->Add(add);
		 }
private: System::Void AddFolderButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ Root = FileTree->SelectedNode;
			 if(!Root)
				 Root = FileTree->Nodes[0];
			 if(Root->Tag)
				 return;
			 Windows::Forms::DialogResult Res = AddFolderDialog->ShowDialog();
			 if(Res == Windows::Forms::DialogResult::OK)
			 {
				 System::IO::DirectoryInfo^ DirInfo = gcnew System::IO::DirectoryInfo(AddFolderDialog->SelectedPath);
				 if(!DirInfo->Name->Contains(L" "))
				 {
					 MergeDirTrees(Root, BuildDirTree(DirInfo));
					 Root->Expand();
				 }
				 else
					 StatusLabel->Text = L"Dir contains spaces!";
			 }
		 }
private: System::Void AddFilesButton_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ Root = FileTree->SelectedNode;
			 if(!Root)
				 Root = FileTree->Nodes[0];
			 if(Root->Tag)
				 return;

			 Windows::Forms::DialogResult Res = AddFilesDialog->ShowDialog();
			 if(Res == Windows::Forms::DialogResult::OK)
			 {
				 for(System::Int32 i = 0; i < AddFilesDialog->FileNames->GetLength(0); i++)
				 {
					 array<System::String^>^ Tokens = AddFilesDialog->FileNames[i]->Split(L'\\');
					 if(Tokens->GetLength(0))
					 {
						 if(!Tokens[Tokens->GetLength(0) - 1]->Contains(L" "))
						 {
							 TreeNode^ ToAdd = gcnew TreeNode(Tokens[Tokens->GetLength(0) - 1]);
							 ToAdd->ImageKey = L"file.bmp";
							 ToAdd->SelectedImageKey = L"file.bmp";
							 ToAdd->Tag = AddFilesDialog->FileNames[i];
							 MergeDirTrees(Root, ToAdd);
						 }
						 else
							 StatusLabel->Text = L"File name contains spaces!";
					 }
				 }
				 Root->Expand();
			 }
		 }
private: System::Void NewFolderButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ Root = FileTree->SelectedNode;
			 if(!Root)
				 Root = FileTree->Nodes[0];
			 if(Root->Tag)
				 return;
			 Root->Nodes->Add("folder");
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			 FileTree->Nodes->Add(L"\\");
		 }
private: System::Void DeleteButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ ToDel = FileTree->SelectedNode;
			 if(ToDel && (ToDel != FileTree->Nodes[0]))
				 ToDel->Remove();
		 }
private: System::Void FileTree_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ Root = FileTree->SelectedNode;
			 if(!Root)
				 Root = FileTree->Nodes[0];
			 if(Root->Tag)
				 return;
			 array<System::String^>^ Files = (array<System::String^>^)e->Data->GetData(DataFormats::FileDrop, false);
			 for(System::Int32 i = 0; i < Files->GetLength(0); i++)
			 {
				 if(System::IO::Directory::Exists(Files[i]))
				 {
					 System::IO::DirectoryInfo^ DirInfo = gcnew System::IO::DirectoryInfo(Files[i]);
					 if(!DirInfo->Name->Contains(L" "))
						 MergeDirTrees(Root, BuildDirTree(DirInfo));
					 else
						 StatusLabel->Text = L"Dir contains spaces!";
				 }
				 else
				 {
					 array<System::String^>^ Tokens = Files[i]->Split(L'\\');
					 if(Tokens->GetLength(0))
					 {
						 if(!Tokens[Tokens->GetLength(0) - 1]->Contains(L" "))
						 {
							 TreeNode^ ToAdd = gcnew TreeNode(Tokens[Tokens->GetLength(0) - 1]);
							 ToAdd->ImageKey = L"file.bmp";
							 ToAdd->SelectedImageKey = L"file.bmp";
							 ToAdd->Tag = Files[i];
							 MergeDirTrees(Root, ToAdd);
						 }
						 else
							 StatusLabel->Text = L"File name contains spaces!";
					 }
				 }
			 }
			 Root->Expand();
		 }
private: System::Void FileTree_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) 
		 {
			 if (e->Data->GetDataPresent(DataFormats::FileDrop, false))
				 e->Effect = DragDropEffects::All;
			 else
				 e->Effect = DragDropEffects::None;
		 }
private: System::Int32 MeasureTree(TreeNode^ node)
		 {
			 System::Int32 Res = 0;
			 for(IEnumerator^ Node = node->Nodes->GetEnumerator(); Node->MoveNext();)
			 {
				 if(node->Tag)
					Res++;
				 else
					(Res += MeasureTree((TreeNode^)Node->Current))++;
			 }
			 return Res;
		 }
public:
	ref class VdfFilePart 
	{
	public:
		String^	VdfFile;
		uInt	Offset;
		uInt	Size;

	public:
		VdfFilePart(String^ file, uInt offset, uInt size)
		{
			VdfFile = file;
			Offset = offset;
			Size = size;
		}
	};
private: System::Boolean WriteFiles(TreeNode^ parent, FILE* vdf, VdfEntryInfo* Entries, Int32& FilledEntries, uInt& NumFiles, uInt& DataSize, uInt TotalEntries)
		 {
			 for(IEnumerator^ Node = parent->Nodes->GetEnumerator(); Node->MoveNext();)
			 {
				 TreeNode^ node = (TreeNode^)Node->Current;
				 VdfEntryInfo& Entrie = Entries[FilledEntries++];

				 pin_ptr<const wchar_t> FromName = PtrToStringChars(node->Text);
				 size_t len = 0;
				 wcstombs_s(&len, Entrie.Name, FromName, 64);
				 _strupr_s(Entrie.Name, len);
				 memset(&Entrie.Name[node->Text->Length], 0x20, sizeof(Entrie.Name) - node->Text->Length);

				 if(node->Tag)
				 {
					 Entrie.Type = 0;
					 Entrie.JumpTo = ftell(vdf);
					 Entrie.Attrib = 0x20;

					 if(node->Tag->GetType() == String::typeid)
					 {
						 FILE* src = NULL;
						 pin_ptr<const wchar_t> Source = PtrToStringChars((String^)node->Tag);
						 if(_wfopen_s(&src, Source, L"rb"))
							 return false;

						 fseek(src, 0, SEEK_END);
						 Entrie.Size = ftell(src);
						 NumFiles++;
						 DataSize += Entrie.Size;
						 fseek(src, 0, SEEK_SET);

						 char* Buffer = new char[0x10000];
						 for(uInt readed = 0; readed < Entrie.Size; )
						 {
							 size_t ToRead = 0x10000;
							 if(ToRead > Entrie.Size - readed)
								ToRead = Entrie.Size - readed;
							 size_t res = fread(Buffer, 1, ToRead, src);
							 if(res != ToRead)
							 {
								 delete[] Buffer;
								 fclose(src);
								 return false;
							 }
							 fwrite(Buffer, 1, res, vdf);
							 readed += res; 
						 }
						 delete[] Buffer;
						 fclose(src);
					 }
					 else
					 {
						 if(node->Tag->GetType() == VdfFilePart::typeid)
						 {
							 VdfFilePart^ VdfTag =(VdfFilePart^)node->Tag;

							 FILE* src = NULL;
							 pin_ptr<const wchar_t> Source = PtrToStringChars(VdfTag->VdfFile);
							 if(_wfopen_s(&src, Source, L"rb"))
								 return false;

							 fseek(src, VdfTag->Offset, SEEK_SET);
							 Entrie.Size = VdfTag->Size;
							 NumFiles++;
							 DataSize += Entrie.Size;

							 char* Buffer = new char[0x10000];
							 for(uInt readed = 0; readed < Entrie.Size; )
							 {
								 size_t ToRead = 0x10000;
								 if(ToRead > Entrie.Size - readed)
									ToRead = Entrie.Size - readed;
								 size_t res = fread(Buffer, 1, ToRead, src);
								 if(res != ToRead)
								 {
									 delete[] Buffer;
									 fclose(src);
									 return false;
								 }
								 fwrite(Buffer, 1, res, vdf);
								 readed += res; 
							 }
							 delete[] Buffer;
							 fclose(src);
						 }
					 }
				 }
				 else
				 {
					 Entrie.Type = VDF_ENTRY_DIR;
					 Entrie.JumpTo = FilledEntries;
					 Entrie.Size = 0;
					 Entrie.Attrib = 0;
					 WriteFiles(node, vdf, Entries, FilledEntries, NumFiles, DataSize, TotalEntries);
				 }
				 if(node == node->Parent->Nodes[node->Parent->Nodes->Count - 1])
					Entrie.Type |= VDF_ENTRY_LAST;

				 StatusLabel->Text = String::Format("{0:0}", (100.0f * FilledEntries / TotalEntries));
				 StatusLabel->Update();
			 }
			 return true;
		 }
private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) 
		 {
			 StatusLabel->Text = L"OK";
			 Int32 NumEntries = MeasureTree(FileTree->Nodes[0]);
			 if(NumEntries)
			 {
				 Windows::Forms::DialogResult Res = SaveFileDialog->ShowDialog();
				 if(Res == Windows::Forms::DialogResult::OK)
				 {
					 VdfHeader Header;
					 pin_ptr<const wchar_t> Comment = PtrToStringChars(CommentBox->Text);
					 size_t len = 0;
					 wcstombs_s(&len, Header.Comment, Comment, 256);
					 memset(&Header.Comment[CommentBox->Text->Length], 0x1A, sizeof(Header.Comment) - CommentBox->Text->Length);

					 memcpy(Header.Signature, VDF_SIGNATURE_G2, sizeof(VDF_SIGNATURE_G2) - 1);
					 Header.Version = 0x50;
					 Header.NumEntries = NumEntries;
					 Header.Timestamp.Year = TimeStampPicker->Value.Year - 1980;
					 Header.Timestamp.Month = TimeStampPicker->Value.Month;
					 Header.Timestamp.Day = TimeStampPicker->Value.Day;
					 Header.Timestamp.Hour = TimeStampPicker->Value.Hour;
					 Header.Timestamp.Min = TimeStampPicker->Value.Minute;
					 Header.Timestamp.Sec = TimeStampPicker->Value.Second;
					 Header.RootCatOffset = sizeof(VdfHeader);
					 Header.NumFiles = 0;
					 Header.DataSize = 0;

					 Int32 FilledEntries = 0;
					 VdfEntryInfo* Entries = new VdfEntryInfo[NumEntries];

					 pin_ptr<const wchar_t> VdfName = PtrToStringChars(SaveFileDialog->FileName);
					 FILE* out = NULL;
					 if(!_wfopen_s(&out, VdfName, L"wb"))
					 {
						 fwrite(&Header, 1, sizeof(VdfHeader), out);
						 fwrite(Entries, NumEntries, sizeof(VdfEntryInfo), out);

						 if(!WriteFiles(FileTree->Nodes[0], out, Entries, FilledEntries, Header.NumFiles, Header.DataSize, NumEntries))
							 StatusLabel->Text = L"Error";
						 else
							 StatusLabel->Text = L"OK";

						 fseek(out, 0, SEEK_SET);
						 fwrite(&Header, 1, sizeof(VdfHeader), out);
						 fseek(out, sizeof(VdfHeader), SEEK_SET);
						 fwrite(Entries, NumEntries, sizeof(VdfEntryInfo), out);
						 fclose(out);
					 }

					 delete[] Entries;
				 }
			 }
		 }
private: System::Boolean LoadTree(TreeNode^ parent, VdfEntryInfo* Entries, uInt StartIndex, String^ vdffile)
		 {
			 for(uInt e = StartIndex; ; e++)
			 {
				 for(int c = 0; c < sizeof(Entries[e].Name); c++)
				 {
					 if(Entries[e].Name[c] == 0x20)
						 Entries[e].Name[c] = 0x0;
				 }
				 if(Entries[e].Type & VDF_ENTRY_DIR)
				 {
					 if(!LoadTree(parent->Nodes->Add(gcnew String(Entries[e].Name)), Entries, Entries[e].JumpTo, vdffile))
						 return false;
				 }
				 else
				 {
					 TreeNode^ file = parent->Nodes->Add(gcnew String(Entries[e].Name));
					 file->ImageKey = L"file.bmp";
					 file->SelectedImageKey = L"file.bmp";
					 file->Tag = gcnew VdfFilePart(vdffile, Entries[e].JumpTo, Entries[e].Size);
				 }
				 if(Entries[e].Type & VDF_ENTRY_LAST)
					 break;
			 }
			 return true;
		 }
private: System::Void OpenButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 Windows::Forms::DialogResult Res = OpenFileDialog->ShowDialog();
			 if(Res == Windows::Forms::DialogResult::OK)
			 {
				 pin_ptr<const wchar_t> VdfName = PtrToStringChars(OpenFileDialog->FileName);
				 FILE* vdf = NULL;
				 if(!_wfopen_s(&vdf, VdfName, L"rb"))
				 {
					 VdfHeader Header;
					 if(fread(&Header, 1, sizeof(VdfHeader), vdf) != sizeof(VdfHeader))
						 return;
					 for(int c = 0; c < sizeof(Header.Comment); c++)
					 {
						 if(Header.Comment[c] == 0x1A)
							 Header.Comment[c] = 0x0;
					 }
					 
					 CommentBox->Text = gcnew String(Header.Comment);
					 TimeStampPicker->Value = System::DateTime(1980 + Header.Timestamp.Year, Header.Timestamp.Month, Header.Timestamp.Day, Header.Timestamp.Hour, Header.Timestamp.Min, Header.Timestamp.Sec);

					 fseek(vdf, Header.RootCatOffset, SEEK_SET);
					 VdfEntryInfo* Entries = new VdfEntryInfo[Header.NumEntries];
					 if(fread(Entries, sizeof(VdfEntryInfo), Header.NumEntries, vdf) != Header.NumEntries)
					 {
						 delete[] Entries;
						 return;
					 }

					 FileTree->Nodes->Clear();
					 FileTree->Nodes->Add(L"\\");
					 LoadTree(FileTree->Nodes[0], Entries, 0, OpenFileDialog->FileName);

					 delete[] Entries;

					 fclose(vdf);
				 }
			 }
		 }

private: System::Void ClearButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ ToClear = FileTree->SelectedNode;
			 if(!ToClear)
				 ToClear = FileTree->Nodes[0];
			 ToClear->Nodes->Clear();
		 }
private: System::Boolean ExtractFile(TreeNode^ node, String^ name)
		 {
			 if(node->Tag->GetType() == String::typeid)
			 {
				 System::IO::File::Copy((String^)node->Tag, name, true);
				 return true;
			 }
			 else
			 {
				 if(node->Tag->GetType() == VdfFilePart::typeid)
				 {
					 VdfFilePart^ VdfTag =(VdfFilePart^)node->Tag;

					 FILE* src = NULL;
					 pin_ptr<const wchar_t> Source = PtrToStringChars(VdfTag->VdfFile);
					 if(_wfopen_s(&src, Source, L"rb"))
						 return false;
					 FILE* dst = NULL;
					 pin_ptr<const wchar_t> Destination = PtrToStringChars(name);
					 if(_wfopen_s(&dst, Destination, L"wb"))
					 {
						 fclose(src);
						 return false;
					 }

					 fseek(src, VdfTag->Offset, SEEK_SET);
					 uInt Size = VdfTag->Size;

					 char* Buffer = new char[0x10000];
					 for(uInt readed = 0; readed < Size; )
					 {
						 size_t ToRead = 0x10000;
						 if(ToRead > Size - readed)
							ToRead = Size - readed;
						 size_t res = fread(Buffer, 1, ToRead, src);
						 if(res != ToRead)
						 {
							 delete[] Buffer;
							 fclose(src);
							 fclose(dst);
							 return false;
						 }
						 fwrite(Buffer, 1, res, dst);
						 readed += res; 
					 }
					 delete[] Buffer;
					 fclose(src);
					 fclose(dst);
					 return true;
				 }
			 }
			 return false;
		 }
private: System::Boolean ExtractDir(TreeNode^ node, String^ name)
		 {
			 for(IEnumerator^ Node = node->Nodes->GetEnumerator(); Node->MoveNext();)
			 {
				 TreeNode^ Current = (TreeNode^)Node->Current;
				 if(Current->Tag)
				 {
					 if(!ExtractFile(Current, name + Current->FullPath))
						 return false;
				 }
				 else
				 {
					 System::IO::Directory::CreateDirectory(name + Current->FullPath);
					 return ExtractDir(Current, name);
				 }
			 }
			 return true;
		 }
private: System::Void ExtractButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 TreeNode^ ToExtract = FileTree->SelectedNode;
			 if(ToExtract)
			 {
				 if(ToExtract->Tag)
				 {
					 ExtractFileDialog->FileName = ToExtract->Text;
					 Windows::Forms::DialogResult Res = ExtractFileDialog->ShowDialog();
					 if(Res == Windows::Forms::DialogResult::OK)
					 {
						 ExtractFile(ToExtract, ExtractFileDialog->FileName);
					 }
				 }
				 else
				 {
					 Windows::Forms::DialogResult Res = ExtractFolderDialog->ShowDialog();
					 if(Res == Windows::Forms::DialogResult::OK)
					 {
						 ExtractDir(ToExtract, ExtractFolderDialog->SelectedPath);
					 }
				 }
			 }
		 }
private: System::Void FileTree_BeforeLabelEdit(System::Object^  sender, System::Windows::Forms::NodeLabelEditEventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 if(e->Node == FileTree->Nodes[0])
				 e->CancelEdit = true;
		 }
private: System::Void FileTree_AfterLabelEdit(System::Object^  sender, System::Windows::Forms::NodeLabelEditEventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 if(e->Label && (e->Label->Contains(L" ") || (e->Label->Length == 0)))
				 e->CancelEdit = true;
		 }
private: System::Void RenameButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StatusLabel->Text = L"OK";
			 if(FileTree->SelectedNode)
				 FileTree->SelectedNode->BeginEdit();
		 }

};
}

