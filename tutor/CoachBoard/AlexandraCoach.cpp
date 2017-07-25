#include "CoachBoard/AlexandraCoach.h"
#include "Log.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AlexandraCoach::AlexandraCoach(repository::IProfile &profile)
    : m_profile(profile)
{
    LOG(Note, "Enter AlexandraCoach::AlexandraCoach()");
}

void AlexandraCoach::PrepareLesson()
{
    LOG(Note, "Enter AlexandraCoach::PrepareLesson()");
    QFile file(":/html/templates/tests/TypeMeaningTest");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString html =  in.readAll();

    auto words = m_profile.GetLanguage().GetDictionary().GetNWordPairs(5);
    for (size_t i = 0; i < words.size(); ++i) {
        QuestionStep *step = new QuestionStep(*this,
                                              i,
                                              "Translate the word",
                                              html,
                                              words[i].first,
                                              words[i].second);
        x_AddStepPage(std::unique_ptr<StepPage>(step));
    }

    m_results.assign(5, 0);

    {
        QFile file(":/html/templates/tests/Summary");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&file);
        QString html =  in.readAll();
        m_summaryStep = new SummaryStep(*this, "Test Results", html);
        m_summaryStep->signalChanged(0, 0, m_results.size());
        x_AddStepPage(std::unique_ptr<StepPage>(m_summaryStep));
    }
}

void AlexandraCoach::setAnswerStatus(size_t questionIndex, int status)
{
    m_results[questionIndex] = status;
    int correct = std::count(m_results.begin(), m_results.end(), 1);
    int mistakes = std::count(m_results.begin(), m_results.end(), -1);
    m_summaryStep->signalChanged(correct, mistakes, m_results.size());
}

void AlexandraCoach::QuestionStep::onchange(QString value)
{
    m_owner.setAnswerStatus(m_index, value.isEmpty()? 0: value == m_correctAnswer? 1: -1);
}
