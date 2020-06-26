#pragma once
#include <windows.h>
#include <atlstr.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <msclr\marshal.h>





#include "MyForm1.h"

#include "imge_bmp.h"
#include "Segmentation.h"
#include "EdgeDetection.h"
#define PI 3.14159265359


enum formType {
	TRAIN_CONFIRM_FORM = 0,
	CLUSTER_NUMBER_FORM = 1,
	CLUSTER_NAME_FORM = 2,
	TESTING_FORM = 3
};





namespace CVImageProcessing {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::IO;
	using namespace msclr::interop;
	using namespace System::Runtime::InteropServices;



	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	public ref class MyForm : public System::Windows::Forms::Form
	{

		LPCTSTR input, output;
		int Width, Height;
		long Size, new_size;
		BYTE* raw_intensity;
		BYTE* pure_raw_intensity;
		BYTE* buffer;
		int* histogram;
		int* histogram3D;
		BYTE* binaryImage;
		int* labeledImage;
		static boolean confirm = false;
		int clusterNumber;
		String^ trainingClusterName;
		String^ testingClusterName;
		String^ testingResultDistance;
		MyForm^ instance;
		int* sobelMagnitude;
		float* sobelOrientation;
		int* cannyEdgeImage;
		
		

	private: System::Windows::Forms::ToolStripMenuItem^  kMeansToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeans2ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  histogram3DToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeansKClusterToolStripMenuItem;



	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeans3DToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  morphologyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  trainingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  meanFilteringToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;


	private: System::Windows::Forms::ToolStripMenuItem^  testingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  edgeDetectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sobelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussianFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cannyEdgeDetectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  displayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pictureBox1ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pictureBox2ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  chart1ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  chart2ToolStripMenuItem;









	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
		

	public:
		MyForm(void)
		{
			instance = this;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  operationsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->operationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansKClusterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogram3DToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeans3DToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeans2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->morphologyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->meanFilteringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->edgeDetectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sobelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gaussianFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cannyEdgeDetectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->displayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chart1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chart2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->operationsToolStripMenuItem, this->edgeDetectionToolStripMenuItem, this->displayToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1103, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->saveToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveToolStripMenuItem_Click);
			// 
			// operationsToolStripMenuItem
			// 
			this->operationsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->histogramToolStripMenuItem,
					this->kMeansKClusterToolStripMenuItem, this->histogram3DToolStripMenuItem, this->kMeans3DToolStripMenuItem, this->kMeansToolStripMenuItem,
					this->kMeans2ToolStripMenuItem, this->meanFilteringToolStripMenuItem
			});
			this->operationsToolStripMenuItem->Name = L"operationsToolStripMenuItem";
			this->operationsToolStripMenuItem->Size = System::Drawing::Size(73, 20);
			this->operationsToolStripMenuItem->Text = L"Clustering";
			// 
			// histogramToolStripMenuItem
			// 
			this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
			this->histogramToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->histogramToolStripMenuItem->Text = L"Histogram";
			this->histogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramToolStripMenuItem_Click);
			// 
			// kMeansKClusterToolStripMenuItem
			// 
			this->kMeansKClusterToolStripMenuItem->Name = L"kMeansKClusterToolStripMenuItem";
			this->kMeansKClusterToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->kMeansKClusterToolStripMenuItem->Text = L"K-Means K Cluster";
			this->kMeansKClusterToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansKClusterToolStripMenuItem_Click);
			// 
			// histogram3DToolStripMenuItem
			// 
			this->histogram3DToolStripMenuItem->Enabled = false;
			this->histogram3DToolStripMenuItem->Name = L"histogram3DToolStripMenuItem";
			this->histogram3DToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->histogram3DToolStripMenuItem->Text = L"Histogram3D";
			this->histogram3DToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogram3DToolStripMenuItem_Click);
			// 
			// kMeans3DToolStripMenuItem
			// 
			this->kMeans3DToolStripMenuItem->Enabled = false;
			this->kMeans3DToolStripMenuItem->Name = L"kMeans3DToolStripMenuItem";
			this->kMeans3DToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->kMeans3DToolStripMenuItem->Text = L"K-Means 3D";
			this->kMeans3DToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeans3DToolStripMenuItem_Click);
			// 
			// kMeansToolStripMenuItem
			// 
			this->kMeansToolStripMenuItem->Enabled = false;
			this->kMeansToolStripMenuItem->Name = L"kMeansToolStripMenuItem";
			this->kMeansToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->kMeansToolStripMenuItem->Text = L"K-Means";
			this->kMeansToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansToolStripMenuItem_Click);
			// 
			// kMeans2ToolStripMenuItem
			// 
			this->kMeans2ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->morphologyToolStripMenuItem,
					this->trainingToolStripMenuItem, this->testingToolStripMenuItem
			});
			this->kMeans2ToolStripMenuItem->Name = L"kMeans2ToolStripMenuItem";
			this->kMeans2ToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->kMeans2ToolStripMenuItem->Text = L"K-Means 2 Binary";
			this->kMeans2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeans2ToolStripMenuItem_Click);
			// 
			// morphologyToolStripMenuItem
			// 
			this->morphologyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->dilationToolStripMenuItem,
					this->erosionToolStripMenuItem, this->openingToolStripMenuItem, this->closingToolStripMenuItem
			});
			this->morphologyToolStripMenuItem->Name = L"morphologyToolStripMenuItem";
			this->morphologyToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->morphologyToolStripMenuItem->Text = L"Morphology";
			// 
			// dilationToolStripMenuItem
			// 
			this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
			this->dilationToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->dilationToolStripMenuItem->Text = L"Dilation";
			this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
			// 
			// erosionToolStripMenuItem
			// 
			this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
			this->erosionToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->erosionToolStripMenuItem->Text = L"Erosion";
			this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
			// 
			// openingToolStripMenuItem
			// 
			this->openingToolStripMenuItem->Name = L"openingToolStripMenuItem";
			this->openingToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->openingToolStripMenuItem->Text = L"Opening";
			this->openingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openingToolStripMenuItem_Click);
			// 
			// closingToolStripMenuItem
			// 
			this->closingToolStripMenuItem->Name = L"closingToolStripMenuItem";
			this->closingToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->closingToolStripMenuItem->Text = L"Closing";
			this->closingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closingToolStripMenuItem_Click);
			// 
			// trainingToolStripMenuItem
			// 
			this->trainingToolStripMenuItem->Name = L"trainingToolStripMenuItem";
			this->trainingToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->trainingToolStripMenuItem->Text = L"Training";
			this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::trainingToolStripMenuItem_Click);
			// 
			// testingToolStripMenuItem
			// 
			this->testingToolStripMenuItem->Name = L"testingToolStripMenuItem";
			this->testingToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->testingToolStripMenuItem->Text = L"Testing";
			this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::testingToolStripMenuItem_Click);
			// 
			// meanFilteringToolStripMenuItem
			// 
			this->meanFilteringToolStripMenuItem->Name = L"meanFilteringToolStripMenuItem";
			this->meanFilteringToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->meanFilteringToolStripMenuItem->Text = L"Mean Filtering";
			this->meanFilteringToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::meanFilteringToolStripMenuItem_Click);
			// 
			// edgeDetectionToolStripMenuItem
			// 
			this->edgeDetectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->sobelToolStripMenuItem,
					this->gaussianFilterToolStripMenuItem, this->cannyEdgeDetectionToolStripMenuItem, this->lineToolStripMenuItem
			});
			this->edgeDetectionToolStripMenuItem->Name = L"edgeDetectionToolStripMenuItem";
			this->edgeDetectionToolStripMenuItem->Size = System::Drawing::Size(99, 20);
			this->edgeDetectionToolStripMenuItem->Text = L"Edge Detection";
			// 
			// sobelToolStripMenuItem
			// 
			this->sobelToolStripMenuItem->Name = L"sobelToolStripMenuItem";
			this->sobelToolStripMenuItem->Size = System::Drawing::Size(191, 22);
			this->sobelToolStripMenuItem->Text = L"Sobel";
			this->sobelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::sobelToolStripMenuItem_Click);
			// 
			// gaussianFilterToolStripMenuItem
			// 
			this->gaussianFilterToolStripMenuItem->Name = L"gaussianFilterToolStripMenuItem";
			this->gaussianFilterToolStripMenuItem->Size = System::Drawing::Size(191, 22);
			this->gaussianFilterToolStripMenuItem->Text = L"Gaussian Filter";
			this->gaussianFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::gaussianFilterToolStripMenuItem_Click);
			// 
			// cannyEdgeDetectionToolStripMenuItem
			// 
			this->cannyEdgeDetectionToolStripMenuItem->Name = L"cannyEdgeDetectionToolStripMenuItem";
			this->cannyEdgeDetectionToolStripMenuItem->Size = System::Drawing::Size(191, 22);
			this->cannyEdgeDetectionToolStripMenuItem->Text = L"Canny Edge Detection";
			this->cannyEdgeDetectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cannyEdgeDetectionToolStripMenuItem_Click);
			// 
			// lineToolStripMenuItem
			// 
			this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			this->lineToolStripMenuItem->Size = System::Drawing::Size(191, 22);
			this->lineToolStripMenuItem->Text = L"Line Detection";
			this->lineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::lineToolStripMenuItem_Click);
			// 
			// displayToolStripMenuItem
			// 
			this->displayToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->pictureBox1ToolStripMenuItem,
					this->pictureBox2ToolStripMenuItem, this->chart1ToolStripMenuItem, this->chart2ToolStripMenuItem
			});
			this->displayToolStripMenuItem->Name = L"displayToolStripMenuItem";
			this->displayToolStripMenuItem->Size = System::Drawing::Size(57, 20);
			this->displayToolStripMenuItem->Text = L"Display";
			// 
			// pictureBox1ToolStripMenuItem
			// 
			this->pictureBox1ToolStripMenuItem->Name = L"pictureBox1ToolStripMenuItem";
			this->pictureBox1ToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->pictureBox1ToolStripMenuItem->Text = L"PictureBox1";
			this->pictureBox1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1ToolStripMenuItem_Click);
			// 
			// pictureBox2ToolStripMenuItem
			// 
			this->pictureBox2ToolStripMenuItem->Name = L"pictureBox2ToolStripMenuItem";
			this->pictureBox2ToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->pictureBox2ToolStripMenuItem->Text = L"PictureBox2";
			this->pictureBox2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::pictureBox2ToolStripMenuItem_Click);
			// 
			// chart1ToolStripMenuItem
			// 
			this->chart1ToolStripMenuItem->Name = L"chart1ToolStripMenuItem";
			this->chart1ToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->chart1ToolStripMenuItem->Text = L"Chart1";
			this->chart1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::chart1ToolStripMenuItem_Click);
			// 
			// chart2ToolStripMenuItem
			// 
			this->chart2ToolStripMenuItem->Name = L"chart2ToolStripMenuItem";
			this->chart2ToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->chart2ToolStripMenuItem->Text = L"Chart2";
			this->chart2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::chart2ToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(466, 239);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(574, 27);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(485, 239);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 27);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Histogram";
			series1->YValuesPerPoint = 2;
			series2->BorderColor = System::Drawing::Color::Black;
			series2->ChartArea = L"ChartArea1";
			series2->Color = System::Drawing::Color::Yellow;
			series2->Legend = L"Legend1";
			series2->Name = L"Thresholds";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(536, 386);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			this->chart1->Visible = false;
			// 
			// chart2
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(574, 27);
			this->chart2->Name = L"chart2";
			series3->ChartArea = L"ChartArea1";
			series3->Legend = L"Legend1";
			series3->Name = L"Histogram3D";
			this->chart2->Series->Add(series3);
			this->chart2->Size = System::Drawing::Size(517, 386);
			this->chart2->TabIndex = 7;
			this->chart2->Text = L"chart2";
			this->chart2->Visible = false;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1103, 540);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CVImageProcessing";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		
		CString str;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			str = openFileDialog1->FileName;
			input = (LPCTSTR)str;


			//BMP Image Reading
			buffer = LoadBMP(Width, Height, Size, input);
			raw_intensity = ConvertBMPToIntensity(buffer, Width, Height);
			pure_raw_intensity= ConvertBMPToIntensity(buffer, Width, Height);
			/*pure_raw_intensity = new BYTE[Width*Height];

			for (int i = 0; i < Width*Height; i++)
				pure_raw_intensity[i] = raw_intensity[i];
			*/
			pictureBox1->Width = Width;
			pictureBox2->Width = Width;

			pictureBox1->Height = Height;
			pictureBox2->Height = Height;
			
			pictureBox1->ImageLocation = openFileDialog1->FileName;
			

			//Display Gray Image into pictureBox2
			Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
			pictureBox2->Image = surface;
			Color c;
			
			


			for(int row = 0; row < Height; row++ )
				for (int col = 0; col < Width; col++) {
					c = Color::FromArgb( *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));
					surface->SetPixel(col, row, c);
				}

			pictureBox2->Refresh();
		}


	}


	private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		saveFileDialog1->DefaultExt = ".bmp";
		saveFileDialog1->Filter = "Image Files*.BMP|*.BMP";
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			pictureBox2->Image->Save(saveFileDialog1->FileName);

	}


	private: System::Void pictureBox1ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		pictureBox1->Visible = !(pictureBox1->Visible);

	}

	private: System::Void pictureBox2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		pictureBox2->Visible = !(pictureBox2->Visible);
	}

	private: System::Void chart1ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		chart1->Visible = !(chart1->Visible);
	}

	private: System::Void chart2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		chart2->Visible = !(chart2->Visible);
	}



	private: System::Void histogramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	

	
		pictureBox1->Visible = false;
		pictureBox2->Visible = true;
		histogram = new int[256];
		for (int i = 0; i < 256; i++) histogram[i]=0;

		for(int row=0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				histogram[raw_intensity[row*Width+col]]++;
			}

		for (int i = 0; i < 256; i++)
			chart1->Series["Histogram"]->Points->AddXY(i+1,histogram[i]);

		chart1->Visible = true;
		chart2->Visible = false;


	}


	


	private: System::Void kMeansToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		

		int* labelHistogram = new int[256];
		int t1X = 10;	//threshold1
		int t1Y = histogram[t1X];	//threshold1
		int t2X = 150;	//threshold2
		int t2Y = histogram[t2X];	//threshold2

		kMeansClustering(labelHistogram, histogram, t1X, t1Y, t2X, t2Y);
		
		



		chart1->Series["Thresholds"]->Points->AddXY(t1X,4000);
		chart1->Series["Thresholds"]->Points->AddXY(t2X,4000);


		Bitmap^ surface= gcnew Bitmap(pictureBox2->Width,pictureBox2->Height);
		Color c;
		
		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				if (labelHistogram[raw_intensity[row*Width + col] % 256] == t1X) {
					raw_intensity[row*Width + col] = 0;
				}else if (labelHistogram[raw_intensity[row*Width + col] % 256] == t2X) raw_intensity[row*Width + col] = 255;

				//raw_intensity[row*Width + col] = labelHistogram[raw_intensity[row*Width + col]%256]%256;
				c = Color::FromArgb(*(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));
				
				surface->SetPixel(col, row, c);
			}
		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		delete labelHistogram;
		
			
	}





	private: System::Void kMeans2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		int* labelHistogram = new int[256];

		int objectCount = 0;

		int* objectBorders;

		// Mean Filtering for eliminate Noises
		//meanFiltering(raw_intensity, Height, Width);


		int clusterNumber = 2; // i need to take this value from user
		int* k = new int[clusterNumber];


		// K-Means quantization 
		k = kMeansClusteringKCluster(labelHistogram, histogram, clusterNumber);



		for (int i = 0; i < clusterNumber; i++)
			chart1->Series["Thresholds"]->Points->AddXY(k[i], 4000);



		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;


		int k0 = 0;
		int k1 = 0;
		for (int i = 0; i < 256; i++) {

			if (labelHistogram[i] == k[0])
				k0++;

			if (labelHistogram[i] == k[1])
				k1++;

		}


		int background = 255;
		int foreground = 0;

		//Print K-Means Clustered Image
		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				if (labelHistogram[raw_intensity[row*Width + col] % 256] == k[0]) {  // if we want colored with different sharp color number of cluster
					if (k0 > k1) {

						raw_intensity[row*Width + col] = background;

					}
					else raw_intensity[row*Width + col] = foreground;

				}
				else if (labelHistogram[raw_intensity[row*Width + col] % 256] == k[1]) {

					if (k1 > k0) {

						raw_intensity[row*Width + col] = background;

					}
					else raw_intensity[row*Width + col] = foreground;

				}

				//raw_intensity[row*Width + col] = labelHistogram[raw_intensity[row*Width + col] % 256] % 256; 
				c = Color::FromArgb(*(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		// 0 - 1 image 
		binaryImage = convertToBinary(raw_intensity, Height*Width);
		


	}




		

	public: Void startTrainingClusterNameForm() {

		MyForm1^ clusterNameForm = gcnew MyForm1(CLUSTER_NAME_FORM); // 1 is Cluster Number Form MODE

		Application::Run(clusterNameForm);


		trainingClusterName = clusterNameForm->clusterName;
		

	}


	public: Void startTrainingConfirmForm() {
		
		MyForm1^ confirmForm = gcnew MyForm1(TRAIN_CONFIRM_FORM);
		
		Application::Run(confirmForm);
		this->confirm = confirmForm->confirm;
	}
				



	private: System::Void trainingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		
		

		int objectCount = 0;

		int* objectBorders;


		// labeling objects with numbers 
		labeledImage = labelingObjects(binaryImage, Height, Width, objectCount);




		// objectBorders[objcetCount*4] 
		objectBorders = componentBorderExtract(labeledImage, Height, Width, objectCount);



		int* object;
		int objectLenght = 0;

		int objectHeight = 0;
		int objectWidth = 0;
		float* objectHuMoments;
		
		long float* meanObjectHuMoments = new long float[7];

		for (int i = 0; i < 7; i++) { // memset(meanObjectHuMoments,0)
			meanObjectHuMoments[i] = (float)0;
		}


		
		
		String^ fileName = "huMoments.txt";
		StreamWriter^ sw = gcnew StreamWriter(fileName,true); // Append : True
		sw->Close();

		// Take ClusterName from user
		Thread^ confirmForm = gcnew Thread(gcnew ThreadStart(this, &CVImageProcessing::MyForm::startTrainingClusterNameForm));

		confirmForm->Start();
		confirmForm->Join();


		int trainedObjectCount = 0;


		//clusterName String^ to string type transformation
		IntPtr ip = Marshal::StringToHGlobalAnsi(trainingClusterName);
		const char* clusterNameChar = static_cast<const char*>(ip.ToPointer());
		std::string clstrName(clusterNameChar);

		
		StreamReader^ sr = File::OpenText(fileName);

		
		String^ str;
		int lineCount = 0;
		boolean isThereClusterName = false;
		int clusterNameIndex;


		while ((str = sr->ReadLine()) != nullptr)
		{

			//input convert String^ to string
			IntPtr ip = Marshal::StringToHGlobalAnsi(str);
			const char* inputStr = static_cast<const char*>(ip.ToPointer());
			std::string input(inputStr);

			// Güncellenecek olan Kümenin Momenti var ise onun moment deðerlerini güncelle yoksa yeni satýr olarak ekle +++
			if ((input.compare(clstrName) == 0 ) && (lineCount % 9 == 0)) {
				isThereClusterName = true;
				clusterNameIndex = lineCount;
				for (int i = 0; i < 8; i++)
					str = sr->ReadLine();
				trainedObjectCount = Convert::ToInt16(str);
				

			}

			lineCount++;
		}
		sr->Close();
		
	




	


		for (int index = 0; index < objectCount; index++) {
			
			//Objects In Binary Image
			object = componentExtractWithBorder(objectBorders, labeledImage, Height, Width, index, objectLenght, objectHeight, objectWidth);

			

			chart1->Visible = false;

			pictureBox1->Width = objectWidth;

			pictureBox1->Height = objectHeight;

			Bitmap^ surface2 = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);

			pictureBox1->Image = surface2;
			Color c;

			for (int row = 0; row < objectHeight; row++)
				for (int col = 0; col < objectWidth; col++) {

					if (object[row*objectWidth + col] > 0) {

						c = Color::FromArgb(255, 255, 255);
					}
					else if (object[row*objectWidth + col] == 0) {
						c = Color::FromArgb(0, 0, 0);

					}

					/*c = Color::FromArgb(*(object + row * objectWidth + col), *(object + row * objectWidth + col), *(object + row * objectWidth + col));*/

					surface2->SetPixel(col, row, c);
				}

			pictureBox1->Visible = true;
			pictureBox1->Image = surface2;
			pictureBox1->Refresh();

			confirm = false;


			
			//In new thread, create Validation Form
			Thread^ confirmForm = gcnew Thread( gcnew ThreadStart( this, &CVImageProcessing::MyForm::startTrainingConfirmForm) );
			
			confirmForm->Start();
			confirmForm->Join();
		
			
			
			

			if (confirm == true) {

				
				objectHuMoments = huMoments(object, objectHeight, objectWidth);
				
				//Log Transform for cluster HuMoment
				for (int i = 0; i < 7; i++) {
					objectHuMoments[i] = -1 * copysign(1.0, objectHuMoments[i]) * log10(abs(objectHuMoments[i]));
				}

				//find tag in Database(txt dosya) and sum huMoments 

				meanObjectHuMoments[0] += objectHuMoments[0];
				meanObjectHuMoments[1] += objectHuMoments[1];
				meanObjectHuMoments[2] += objectHuMoments[2];
				meanObjectHuMoments[3] += objectHuMoments[3];
				meanObjectHuMoments[4] += objectHuMoments[4];
				meanObjectHuMoments[5] += objectHuMoments[5];
				meanObjectHuMoments[6] += objectHuMoments[6];
				trainedObjectCount++;

			
			}
			



		}


		////Calculating Mean huMoments

		//meanObjectHuMoments[0] /= trainedObjectCount;
		//meanObjectHuMoments[1] /= trainedObjectCount;
		//meanObjectHuMoments[2] /= trainedObjectCount;
		//meanObjectHuMoments[3] /= trainedObjectCount;
		//meanObjectHuMoments[4] /= trainedObjectCount;
		//meanObjectHuMoments[5] /= trainedObjectCount;
		//meanObjectHuMoments[6] /= trainedObjectCount;



		// Güncellenecek olan Kümenin Momenti var ise onun moment deðerlerini güncelle yoksa yeni satýr olarak ekle +++
		if (isThereClusterName) {

			
			StreamWriter^ sw2 = gcnew StreamWriter("tempFile.txt");
			double* hM = new double[7];
			sr = File::OpenText(fileName);
			for (int line = 0; line <= clusterNameIndex; line++) {
				sw2->WriteLine(sr->ReadLine());
			}

			String^ hM1 = sr->ReadLine();
			//String^ to double type transformation
			hM[0] = Convert::ToDouble(hM1);
			meanObjectHuMoments[0] += hM[0];	

			String^ hM2 = sr->ReadLine();
			//String^ to double type transformation
			hM[1] = Convert::ToDouble(hM2);
			meanObjectHuMoments[1] +=  hM[1];

			String^ hM3 = sr->ReadLine();
			//String^ to double type transformation
			hM[2] = Convert::ToDouble(hM3);
			meanObjectHuMoments[2] += hM[2];

			String^ hM4 = sr->ReadLine();
			//String^ to double type transformation
			hM[3] = Convert::ToDouble(hM4);
			meanObjectHuMoments[3] += hM[3];

			String^ hM5 = sr->ReadLine();
			//String^ to double type transformation
			hM[4] = Convert::ToDouble(hM5);
			meanObjectHuMoments[4] += hM[4];

			String^ hM6 = sr->ReadLine();
			//String^ to double type transformation
			hM[5] = Convert::ToDouble(hM6);
			meanObjectHuMoments[5] += hM[5];

			String^ hM7 = sr->ReadLine();
			//String^ to double type transformation
			hM[6] = Convert::ToDouble(hM7);
			meanObjectHuMoments[6] += hM[6];

			

			sw2->WriteLine("{0}", meanObjectHuMoments[0]);
			sw2->WriteLine("{0}", meanObjectHuMoments[1]);
			sw2->WriteLine("{0}", meanObjectHuMoments[2]);
			sw2->WriteLine("{0}", meanObjectHuMoments[3]);
			sw2->WriteLine("{0}", meanObjectHuMoments[4]);
			sw2->WriteLine("{0}", meanObjectHuMoments[5]);
			sw2->WriteLine("{0}", meanObjectHuMoments[6]);
			sw2->WriteLine("{0}", trainedObjectCount);
			
			for (int line = clusterNameIndex + 8; line <= lineCount; line++) {
				sw2->WriteLine(sr->ReadLine());
			}

			// Closing File
			sw2->Close(); 
			sr->Close();
			sw->Null;
			sw2->Null;
			sr->Null;
			//String^ to char* type transformation
			IntPtr ip = Marshal::StringToHGlobalAnsi(fileName);
			const char* fileNameChar = static_cast<const char*>(ip.ToPointer());

			remove(fileNameChar);

			rename("tempFile.txt", fileNameChar);
			sr = File::OpenText(fileName);
			sr->Close();
		}
		else {

			StreamWriter^ sw = gcnew StreamWriter(fileName, true); // Append : True
			sw->WriteLine("{0}", trainingClusterName);


			//Inserting to file Mean huMoments

			sw->WriteLine("{0}", meanObjectHuMoments[0]);
			sw->WriteLine("{0}", meanObjectHuMoments[1]);
			sw->WriteLine("{0}", meanObjectHuMoments[2]);
			sw->WriteLine("{0}", meanObjectHuMoments[3]);
			sw->WriteLine("{0}", meanObjectHuMoments[4]);
			sw->WriteLine("{0}", meanObjectHuMoments[5]);
			sw->WriteLine("{0}", meanObjectHuMoments[6]);
			sw->WriteLine("{0}", trainedObjectCount);



			sw->Close(); // Closing File

		}
		



		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;

		//Print Labeled Image
		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				if (labeledImage[row*Width + col] == 0) {
					raw_intensity[row*Width + col] = labeledImage[row*Width + col];
				}
				if (raw_intensity[row*Width + col] == 255) {
					int a = 0;
				}
				raw_intensity[row*Width + col] = (BYTE)labeledImage[row*Width + col] * 15;
				c = Color::FromArgb(*(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();


	}




	public: Void startTestingForm() {

		MyForm1^ testingForm = gcnew MyForm1(TESTING_FORM);
		testingForm->testingClusterName = this->testingClusterName;
		testingForm->testingResultDistance = this->testingResultDistance;
		Application::Run(testingForm);
	}


	private: System::Void testingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {


		int objectCount = 0;

		int* objectBorders;


		// labeling objects with numbers 
		labeledImage = labelingObjects(binaryImage, Height, Width, objectCount);


		// objectBorders[objcetCount*4] 
		objectBorders = componentBorderExtract(labeledImage, Height, Width, objectCount);



		int* object;
		int objectLenght = 0;
		int objectHeight = 0;
		int objectWidth = 0;
		float* objectHuMoments;
		int trainedObjectCount = 0;
		



		String^ fileName = "huMoments.txt";
				
		StreamReader^ sr = File::OpenText(fileName);



		String^ str;
		int lineCount = 0;
		while ((str = sr->ReadLine()) != nullptr)
			lineCount++;
		
		sr->Close();

		sr = File::OpenText(fileName);
		int clusterCount = lineCount / 9;

		array<String^>^ clusterName = gcnew array<String^>(clusterCount);
		long float* clusterHuMoments = new long float[clusterCount * 7];

		int lineIndex = 0;
		while ((str = sr->ReadLine()) != nullptr)
		{

			// take huMoments in huMoments.txt and calculate average 
			if (lineIndex % 9 == 0 && lineIndex < lineCount) {
				clusterName[lineIndex / 9] = str;
				String^ hM1 = sr->ReadLine();
				String^ hM2 = sr->ReadLine();
				String^ hM3 = sr->ReadLine();
				String^ hM4 = sr->ReadLine();
				String^ hM5 = sr->ReadLine();
				String^ hM6 = sr->ReadLine();
				String^ hM7 = sr->ReadLine();
				clusterHuMoments[(lineIndex / 9)*7 ] = Convert::ToDouble(hM1);
				clusterHuMoments[(lineIndex / 9)*7 + 1] = Convert::ToDouble(hM2);
				clusterHuMoments[(lineIndex / 9)*7 + 2] = Convert::ToDouble(hM3);
				clusterHuMoments[(lineIndex / 9)*7 + 3] = Convert::ToDouble(hM4);
				clusterHuMoments[(lineIndex / 9)*7 + 4] = Convert::ToDouble(hM5);
				clusterHuMoments[(lineIndex / 9)*7 + 5] = Convert::ToDouble(hM6);
				clusterHuMoments[(lineIndex / 9)*7 + 6] = Convert::ToDouble(hM7);
				trainedObjectCount = Convert::ToInt16(sr->ReadLine());
				for (int i = 0; i < 7; i++)
					clusterHuMoments[(lineIndex / 9)*7 + i] /= (float)trainedObjectCount;
			}

			lineIndex+=9;
		}

		sr->Close();


		for (int index = 0; index < objectCount; index++) {

			//Objects In Binary Image
			object = componentExtractWithBorder(objectBorders, labeledImage, Height, Width, index, objectLenght, objectHeight, objectWidth);
			int* objectRaw = componentExtractWithBorder(objectBorders, pure_raw_intensity, Height, Width, index, objectLenght, objectHeight, objectWidth);
			chart1->Visible = false;

			pictureBox1->Width = objectWidth;

			pictureBox1->Height = objectHeight;

			Bitmap^ surface2 = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);

			Color c;

			for (int row = 0; row < objectHeight; row++)
				for (int col = 0; col < objectWidth; col++) {

					/*
					if (object[row*objectWidth + col] > 0) {

						c = Color::FromArgb(255, 255, 255);
					}
					else if (object[row*objectWidth + col] == 0) {
						c = Color::FromArgb(0, 0, 0);

					}*/

					c = Color::FromArgb(*(objectRaw + row*objectWidth + col), *(objectRaw + row * objectWidth + col), *(objectRaw + row * objectWidth + col));

					surface2->SetPixel(col, row, c);
				}

			pictureBox1->Visible = true;
			pictureBox1->Image = surface2;
			pictureBox1->Refresh();

			

			objectHuMoments = huMoments(object, objectHeight, objectWidth);

			//Log Transform for object HuMoment
			for (int i = 0; i < 7; i++) {
				objectHuMoments[i] = -1 * copysign(1.0, objectHuMoments[i]) * log10(abs(objectHuMoments[i]));
			}
			
	

			//Compare, objectHuMoments and Trained HuMoments with Euclidean Distance
			float minDistance;
			int clusterNameIndex = compareWithEuclideanDistance(objectHuMoments, clusterHuMoments, clusterCount, minDistance);
			
			this->testingClusterName = clusterName[clusterNameIndex];
			this->testingResultDistance = Convert::ToString(minDistance);
			
			//In new thread, create Testing Form
			Thread^ testingForm = gcnew Thread(gcnew ThreadStart(this, &CVImageProcessing::MyForm::startTestingForm));

			testingForm->Start();
			testingForm->Join();

		}


		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;

		//Print Labeled Image
		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				if (labeledImage[row*Width + col] == 0) {
					raw_intensity[row*Width + col] = labeledImage[row*Width + col];
				}
				if (raw_intensity[row*Width + col] == 255) {
					int a = 0;
				}
				raw_intensity[row*Width + col] = (BYTE)labeledImage[row*Width + col] * 15;
				c = Color::FromArgb(*(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();




	}
	



	

	public: Void startClusterNumberForm() {

		MyForm1^ clusterCountForm = gcnew MyForm1(CLUSTER_NUMBER_FORM); // 1 is Cluster Number Form MODE

		Application::Run(clusterCountForm);
		
		
		String^ clusterNum = clusterCountForm->clusterCount;
		IntPtr ip = Marshal::StringToHGlobalAnsi(clusterNum);
		const char* clusterNumChar = static_cast<const char*>(ip.ToPointer());
		clusterNumber = atoi(clusterNumChar);

	}




	private: System::Void kMeansKClusterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		int* labelHistogram = new int[256];
		
		int objectCount = 0;

		int* objectBorders;


		//In new thread, create ClusterNumber Form
		Thread^ clusterNumberForm = gcnew Thread(gcnew ThreadStart(this, &CVImageProcessing::MyForm::startClusterNumberForm));

		clusterNumberForm->Start();
		clusterNumberForm->Join();

		// i need to take this value from user+++
		int* k = new int[clusterNumber];


		// K-Means quantization 
		k = kMeansClusteringKCluster(labelHistogram, histogram, clusterNumber); 

	

		for(int i =0;i<clusterNumber;i++)
			chart1->Series["Thresholds"]->Points->AddXY(k[i], 4000);



		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;
		

		int k0 = 0;
		int k1 = 0;
		for (int i = 0; i < 256; i++) {

			if (labelHistogram[i] == k[0])
				k0++;

			if (labelHistogram[i] == k[1])
				k1++;

		}

		//Print K-Means Clustered Image
			for (int row = 0; row < Height; row++)
				for (int col = 0; col < Width; col++) {
					
					raw_intensity[row*Width + col] = labelHistogram[raw_intensity[row*Width + col] % 256] % 256; 
					c = Color::FromArgb(*(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));

					surface->SetPixel(col, row, c);
				}

			pictureBox2->Image = surface;
			pictureBox2->Refresh();


		
	}






	private: System::Void meanFilteringToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		//Mean Filtering Raw Image 
		meanFiltering(raw_intensity, Height, Width);


		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;


		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {


				

				c = Color::FromArgb(*(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col), *(raw_intensity + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		
	}

	private: System::Void dilationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
		
		dilation(binaryImage, Height, Width);


		BYTE* printingBinary = new BYTE[Height*Width];
		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;

		
		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				
				
				if (binaryImage[row*Width+col] == 0) {  
					printingBinary[row*Width + col] = 0;
				}
				else if (binaryImage[row*Width + col] == 1) {

					printingBinary[row*Width + col] = 255;

				}

				
				c = Color::FromArgb(*(printingBinary + row * Width + col), *(printingBinary + row * Width + col), *(printingBinary + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		delete printingBinary;
	}

	private: System::Void erosionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
		erosion(binaryImage, Height, Width);

		BYTE* printingBinary = new BYTE[Height*Width];
		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;


		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {


				if (binaryImage[row*Width + col] == 0) {
					printingBinary[row*Width + col] = 0;
				}
				else if (binaryImage[row*Width + col] == 1) {

					printingBinary[row*Width + col] = 255;

				}


				c = Color::FromArgb(*(printingBinary + row * Width + col), *(printingBinary + row * Width + col), *(printingBinary + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		delete printingBinary;
	}

	private: System::Void openingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
		opening(binaryImage, Height, Width);

		BYTE* printingBinary = new BYTE[Height*Width];
		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;


		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {


				if (binaryImage[row*Width + col] == 0) {
					printingBinary[row*Width + col] = 0;
				}
				else if (binaryImage[row*Width + col] == 1) {

					printingBinary[row*Width + col] = 255;

				}


				c = Color::FromArgb(*(printingBinary + row * Width + col), *(printingBinary + row * Width + col), *(printingBinary + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		delete printingBinary;

	}

	private: System::Void closingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {


		closing(binaryImage, Height, Width);

		BYTE* printingBinary = new BYTE[Height*Width];
		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		Color c;


		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {


				if (binaryImage[row*Width + col] == 0) {
					printingBinary[row*Width + col] = 0;
				}
				else if (binaryImage[row*Width + col] == 1) {

					printingBinary[row*Width + col] = 255;

				}


				c = Color::FromArgb(*(printingBinary + row * Width + col), *(printingBinary + row * Width + col), *(printingBinary + row * Width + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		delete printingBinary;

	}





	private: System::Void histogram3DToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		pictureBox1->Visible = true;
		pictureBox2->Visible = true;

		histogram3D = new int[256*256*256];
		for (int i = 0; i < 256*256*256; i++) histogram3D[i] = 0;

		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width*3; col+=3) {
				histogram3D[buffer[row*Width * 3 + col] * 256 * 256 + buffer[row*Width * 3 + col + 1] * 256 + buffer[row*Width * 3 + col + 2]]++;//(blue,green,red) the way how its mapped.
			}

		/*for (int i = 0; i < 256*3; i++) {

			chart2->Series["Histogram3D"]->Points->AddXY(i + 1, histogram3D[i]);
			

		}*/

		chart1->Visible = false;
		chart2->Visible = false;

		

	}

	private: System::Void kMeans3DToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		int* labelHistogram3D = new int[256 * 256 * 256]; //labelHist3D(red,green,blue) dimentions
		

		int clusterNumber = 10; // i need to take this value from user
		int* k3D = new int[clusterNumber*3]; //(blue, green, red) dimentions

		k3D = kMeansClustering3D(labelHistogram3D, histogram3D, clusterNumber);




		/*for (int i = 0; i < clusterNumber; i++)
			chart1->Series["Thresholds"]->Points->AddXY(k[i], 4000);*/


		chart2->Visible = false;
		pictureBox2->Image = pictureBox1->Image;
		pictureBox2->Visible = true;


		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Color c;
		BYTE* rgbColor=new BYTE[3];
		for (int row = 0; row < Height; row++)
			for (int col = 0; col < Width; col++) {
				//if (labelHistogram3D[buffer[(Height - row - 1) * Width * 3 + col * 3]] == k3D[clusterNumber]) {  // if we want colored with different sharp color number of cluster
				//	buffer[(Height - row - 1) * Width * 3 + col * 3] = 0;
				//	buffer[(Height - row - 1) * Width * 3 + col * 3 + 1] = 0;
				//	buffer[(Height - row - 1) * Width * 3 + col * 3 + 2] = 0;
				//}
				//else if (labelHistogram3D[buffer[(Height - row - 1) * Width * 3 + col * 3]] == k3D[clusterNumber]) raw_intensity[row*Width + col] = 255;


				/*rgbColor[0] = buffer[(Height - row - 1) * Width * 3 + col * 3];
				rgbColor[0] = labelHistogram3D[rgbColor[2]];*/
				int indexOfCluster = labelHistogram3D[buffer[(Height - row - 1) * Width * 3 + col * 3] * 256 * 256 + buffer[(Height - row - 1) * Width * 3 + col * 3 + 1] * 256 + buffer[(Height - row - 1) * Width * 3 + col * 3 + 2]];
				rgbColor[0] = k3D[indexOfCluster];



				/*rgbColor[1] = buffer[(Height - row - 1) * Width * 3 + col * 3];
				rgbColor[1] = labelHistogram3D[rgbColor[2]];*/
				rgbColor[1] = k3D[indexOfCluster+1];


				/*rgbColor[2] = buffer[(Height - row - 1) * Width * 3 + col * 3];
				rgbColor[2] = labelHistogram3D[rgbColor[2]];*/
				rgbColor[2] = k3D[indexOfCluster+2];



				buffer[(Height - row - 1) * Width * 3 + col * 3]		= rgbColor[0]; //blue
				buffer[(Height - row - 1) * Width * 3 + col * 3 + 1]	= rgbColor[1];//green
				buffer[(Height - row - 1) * Width * 3 + col * 3 + 2]	= rgbColor[2]; //red
				
				c = Color::FromArgb(buffer[(Height - row - 1) * Width * 3 + col * 3], buffer[(Height - row - 1) * Width * 3 + col * 3 +1], buffer[(Height - row - 1) * Width * 3 + col * 3 +2]);

				



				surface->SetPixel(col, row, c);
			}
		pictureBox1->Image = surface;
		pictureBox1->Refresh();
		
		
		
		delete labelHistogram3D;

	}











	
	private: System::Void sobelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		sobelMagnitude = new int[(Height - 2)*(Width - 2)];
		sobelOrientation = new float[(Height - 2)*(Width - 2)];

		int* sobelImage = new int[(Height - 2)*(Width - 2)];
		sobel(raw_intensity, Height, Width, sobelMagnitude, sobelOrientation);


		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width-2, pictureBox2->Height-2);
		Color c;

		int max = sobelMagnitude[0];
		for (int row = 0; row < Height - 2; row++)
			for (int col = 0; col < Width - 2; col++) {
				int pos = row * (Width - 2) + col; // image position
				
				if (sobelMagnitude[pos] > max) {
					max = sobelMagnitude[pos];
				}
			}

		for (int row = 0; row < Height - 2; row++)
			for (int col = 0; col < Width - 2; col++) {

				int pos = row * (Width-2) + col; // image position
				sobelImage[pos] = sobelMagnitude[pos];
				sobelImage[pos] = (int) sobelImage[pos] * (255.0 / max);
				if (sobelImage[pos] > 255)
					sobelImage[pos] = 255;
				c = Color::FromArgb(*(sobelImage + row * (Width - 2) + col), *(sobelImage + row * (Width - 2)+ col), *(sobelImage + row * (Width - 2)+ col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		
	}

	private: System::Void gaussianFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
		//5x5 gaussian Mask used
		BYTE* gaussianImage = gaussianFilter(raw_intensity, Height, Width);
		

		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width , pictureBox2->Height);
		Color c;


		for (int row = 0; row < Height ; row++)
			for (int col = 0; col < Width ; col++) {

				raw_intensity[row*Width + col] = gaussianImage[row*Width + col];
				c = Color::FromArgb(*(gaussianImage + row * Width + col), *(gaussianImage + row * Width  + col), *(gaussianImage + row * Width  + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();

		

		delete gaussianImage;
	}


	private: System::Void cannyEdgeDetectionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		
		cannyEdgeImage = cannyEdgeDetector(raw_intensity,Height,Width,sobelMagnitude,sobelOrientation);


		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width-2, pictureBox2->Height-2);
		Color c;

		//finding max member of sobelMagnitude
		int max = cannyEdgeImage[0];
		for (int row = 0; row < Height - 2; row++)
			for (int col = 0; col < Width - 2; col++) {

				int pos = row * (Width - 2) + col;
				if (cannyEdgeImage[pos] > max) {

					max = cannyEdgeImage[pos];
				}

			}

		for (int row = 0; row < Height - 2; row++)
			for (int col = 0; col < Width - 2; col++) {
				int pos = row * (Width - 2) + col; // image position

				if (cannyEdgeImage[pos] == 1) {
					cannyEdgeImage[pos] = 255;
				}
				
				//cannyEdgeImage[pos] = cannyEdgeImage[pos]*255/max;

				c = Color::FromArgb(*(cannyEdgeImage + row * (Width - 2) + col), *(cannyEdgeImage + row * (Width - 2) + col), *(cannyEdgeImage + row * (Width - 2) + col));

				surface->SetPixel(col, row, c);
			}

		pictureBox2->Image = surface;
		pictureBox2->Refresh();




	}

	private: System::Void lineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		
		int pixelLocationOfLineLenght;
		int* mostSignificantLine;
		int lineCount = 8;
		int* pixelLocationOfLine = houghTransformWithOrientation(cannyEdgeImage, Height, Width, sobelOrientation, lineCount, pixelLocationOfLineLenght, mostSignificantLine);
		

		

		Bitmap^ surface = gcnew Bitmap(pictureBox2->Width-2, pictureBox2->Height-2);
		Color c;

		for (int row = 0; row < Height - 2; row++)
			for (int col = 0; col < Width - 2; col++) {
				int pos = row * (Width - 2) + col; // image position

				
				c = Color::FromArgb(*(cannyEdgeImage + row * (Width - 2) + col), *(cannyEdgeImage + row * (Width - 2) + col), *(cannyEdgeImage + row * (Width - 2) + col));

				surface->SetPixel(col, row, c);
			}
		
		// Green HoughPosition coloring
		for (int index = 0; index < pixelLocationOfLineLenght; index++) {
			//int edgePos = row * (width - 2) + col;
			int pos = pixelLocationOfLine[index];

			int col = pos % (Width - 2);
			int row = (pos - col) / (Width - 2);

			c = Color::FromArgb(0, 255, 0);

			surface->SetPixel(col, row, c);
		}

		int redCount = 0;
		for (int line = 0; line < lineCount; line++) {
			
			int houghPos = mostSignificantLine[line];
		
			//houghPos => dis * 180 + (angle + 90);
			

			double angle = (houghPos)%180;
			int dis = (houghPos - angle) / 180;
			angle = angle - 90;
			
			int y = sin(angle * PI / 180.0)*dis;
			int x = cos(angle * PI / 180.0)*dis;

			int edgeDirection = angle - 90.0;

			if (edgeDirection > 90) {
				edgeDirection -= 180;
			}
			else if (edgeDirection < -90) {
				edgeDirection += 180;

			}
			


			if (edgeDirection == 90 || edgeDirection == -90) { // eðim sonsuz
				
				for (int row = 0; row < Height - 2; row++) {

					int col = x;
					if (col >= 0 && col < Width - 2) {
						c = Color::FromArgb(255, 0, 0);
						redCount++;
						surface->SetPixel(col, row, c);
					}
				}
					
			}
			else if (edgeDirection == 0) { // eðim 0
			
				for (int col = 0; col < Width - 2; col++) {

					int row = -1*y;
					if (row >= 0 && row < Height - 2) {
						c = Color::FromArgb(255, 0, 0);
						redCount++;
						surface->SetPixel(col, row, c);
					}
				}
			}else if ((edgeDirection > 45 && edgeDirection < 90 ) || (edgeDirection < -45 && edgeDirection > -90)) {

				double slope = tan(edgeDirection * PI / 180.0); // eðim

				int b = round(-1 * slope * x + y);

				for (int row = 0; row < Height - 2; row++) {

					int col = (row - b) / slope;
					if (col >= 0 && col < Width - 2) {
						c = Color::FromArgb(255, 0, 0);
						redCount++;
						surface->SetPixel(col, row, c);
					}
				}
			}
			else if (edgeDirection <= 45 && edgeDirection >= -45 ) {

				double slope = tan(edgeDirection * PI / 180.0); // eðim
				
				int b = round(-1 * slope * x + y);

				for (int col = 0; col < Width - 2; col++) {

					int row = slope * col + b;
					if (row >= 0 && row < Height - 2) {
						c = Color::FromArgb(255, 0, 0);
						redCount++;
						surface->SetPixel(col, row, c);
					}
				}
			}

			
			pictureBox2->Image = surface;
			pictureBox2->Refresh();
		}



		pictureBox2->Image = surface;
		pictureBox2->Refresh();




	}

	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		
		delete[] buffer;
		delete[] raw_intensity;
		delete[] histogram;
		delete[] histogram3D;
		delete[] sobelMagnitude;
		delete[] sobelOrientation;
		delete[] cannyEdgeImage;
		delete[] pure_raw_intensity;
		delete[] labeledImage;
		delete[] binaryImage;


	}







};
}
