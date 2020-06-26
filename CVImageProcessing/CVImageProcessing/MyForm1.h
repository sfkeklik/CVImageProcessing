#pragma once

class MyForm;



namespace CVImageProcessing {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for MyForm1	
	/// </summary>

	
	public ref class MyForm1 : public System::Windows::Forms::Form
	{

		
	public:	boolean confirm;
	public: String^ clusterCount;
	public: String^ clusterName;
	public: String^ testingResultDistance;
	public: String^ testingClusterName;
	public: int formMode;




	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label6;

	private: System::Windows::Forms::Button^  button4;


	public:
		MyForm1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}


		MyForm1(int mode)
		{
			formMode = mode;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(108, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Add to Train \?";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(36, 49);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Yes";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(177, 49);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"No";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm1::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(23, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Cluster Number";
			this->label2->Visible = false;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(93, 36);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(70, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"Submit";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm1::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(26, 36);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(61, 20);
			this->textBox1->TabIndex = 7;
			this->textBox1->Visible = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(23, 20);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Cluster Name";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(93, 36);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(70, 23);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Submit";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm1::button4_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(99, 20);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(23, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"It is";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(121, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"label5";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(93, 49);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(70, 23);
			this->button5->TabIndex = 14;
			this->button5->Text = L"OK";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm1::button5_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(121, 36);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"label6";
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 99);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm1";
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		//Training YES
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
		confirm = true;
		Form::Close();

	}

		//Training NO
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		confirm = false;
		Form::Close();
	}


	//Cluster Count which is K means K cluster's image result
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		clusterCount = textBox1->Text;
		Form::Close();
	}

	//Training Cluster Name Send Button
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

		clusterName = textBox1->Text;
		Form::Close();

	}

	//Testing OK Button
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	
		Form::Close();
	}

	private: System::Void MyForm1_Load(System::Object^  sender, System::EventArgs^  e) {
	
		if (formMode == 0) { // Training Confirm Mode
			label1->Visible = true;
			button1->Visible = true;
			button2->Visible = true;

			label2->Visible = false;
			label3->Visible = false;
			textBox1->Visible = false;
			button3->Visible = false;
			button4->Visible = false;
			label4->Visible = false;
			label5->Visible = false;
			button5->Visible = false;
			label6->Visible = false;
		}else if (formMode == 1) { // K means K Cluster Count Mode
			label2->Visible = true;
			textBox1->Visible = true;
			button3->Visible = true;

			label1->Visible = false;
			button1->Visible = false;
			button2->Visible = false;
			label3->Visible = false;
			button4->Visible = false;
			label4->Visible = false;
			label5->Visible = false;
			button5->Visible = false;
			label6->Visible = false;
		}else if (formMode == 2) { // Training Cluster Name Mode
			label3->Visible = true;
			textBox1->Visible = true;
			button4->Visible = true;

			label1->Visible = false;
			button1->Visible = false;
			button2->Visible = false;
			label2->Visible = false;
			button3->Visible = false;
			label4->Visible = false;
			label5->Visible = false;
			button5->Visible = false;
			label6->Visible = false;
		}
		else if (formMode == 3) {// Testing Mode
			label4->Visible = true;
			label5->Text = testingClusterName;
			label5->Visible = true;
			label6->Text = testingResultDistance;
			label6->Visible = true;
			button5->Visible = true;

			label3->Visible = false;
			textBox1->Visible = false;
			button4->Visible = false;
			label1->Visible = false;
			button1->Visible = false;
			button2->Visible = false;
			label2->Visible = false;
			button3->Visible = false;
		}
	
	}


};
}
